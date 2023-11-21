/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/table/vector_table.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <string>

#include "roastdb/storage/table/table.h"

namespace roastdb {

/// @brief VectorTable serve as temporary buffer between SQL pipelines, it only
/// supports buffer interfaces and other concurrency functionalities.
class VectorTable : public Table {
public:
    enum class State {
        Empty, Writing, Full, Reading,
    };

    DISALLOW_COPY(VectorTable)
    DISALLOW_MOVE(VectorTable)

    using Tuple = _MaterializedTuple;

    VectorTable(
        table_id_t table_id,
        const std::vector<ColumnInfo>& columns,
        const std::vector<column_id_t>& key_attrs
    ):  Table(
            TableType::Vector,
            table_id,
            "__vector_" + std::to_string(table_id),
            columns
        ), state_(State::Empty) {}

    State state() const { return state_; }

    inline void begin_ope(State state) {
        state_ = state;
        if (state_ == State::Writing) {
            tuples_.clear();
        }
    }

    inline void end_ope() {
        if (state_ == State::Writing) {
            state_ = State::Full;
        } else if (state_ == State::Reading) {
            state_ = State::Empty;
        }
    }

    inline void reserve(size_t size) { tuples_.reserve(size); }

    inline void write(Tuple&& tuple) { tuples_.push_back(std::move(tuple)); }

    inline const Tuple& read(RID rid) const { return tuples_[rid]; }

    inline size_t size() const { return tuples_.size(); }

private:
    State state_;

    std::vector<Tuple> tuples_;
};

}