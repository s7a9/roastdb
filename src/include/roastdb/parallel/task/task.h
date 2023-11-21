/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/parallel/task/task.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include "roastdb/common/db_config.h"
#include "roastdb/common/macros.h"

namespace roastdb {

/// @brief Task is the basic unit of work in RoastDB.
class Task {
    friend class TaskScheduler;

public:
    constexpr static bool READ = false, WRITE = true;

    enum class State : uint8_t {
        Initialized,    /// Task is initialized.
        Ready,          /// Task is ready to execute.
        Executing,      /// Task is executing.
        Stalled,        /// Task is stalled.
        Finished,       /// Task is finished.
        Aborted,        /// @brief Task is aborted.
        Invalid = -1,   /// Task is invalid.
    };

    DISALLOW_COPY(Task)

    Task(bool access_type, table_id_t table_id = INVALID_TABLE_ID): 
        access_type_(access_type), table_id_(table_id) {}

    virtual ~Task() = default;

    /// @brief Get the state of the task.
    /// @return the state of the task.
    inline State state() const { return state_; }

    inline bool access_type() const { return access_type_; }

    inline table_id_t table_id() const { return table_id_; }

protected:
    virtual State execute() = 0;

    virtual State execute_from_stalled() { return execute(); }

    bool access_type_;

    table_id_t table_id_;

    State state_ = State::Initialized;
};

}