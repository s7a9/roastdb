/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/disk/disk_manager_win.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <string>
#include <memory>
#include <mutex>
#include <queue>

#include "roastdb/common/db_config.h"
#include "roastdb/parallel/locks/rwlock.h"
#include "roastdb/storage/disk/disk_request.h"

namespace roastdb {

class DiskManager {
public:
    explicit DiskManager(const std::string& db_filename);

    ~DiskManager();

    inline bool is_open() const;

    /// @brief wait for reqeust to be done and close the file.
    void shutdown();

    /// @brief synchronously proceesing the request
    /// @param request 
    void perform(std::shared_ptr<DiskRequest> request);

    /// @brief asynchronously proceesing the request, this will immediately return
    /// @param request 
    void schedule(std::shared_ptr<DiskRequest> request);

private:
    void* hfile_;

    RWLock file_rwlock_;

    std::queue<std::shared_ptr<DiskRequest>> req_queue_;

    std::mutex req_queue_m_;
};

}