/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/disk/disk_request.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <cstdint>
#include <atomic>

#include "roastdb/common/db_config.h"

namespace roastdb {

struct DiskRequest {
    enum class Type : uint8_t {
        Fetch, Flush,
    } type;

    enum class Status : uint8_t {
        Ready, Processing, Completed, Aborted,
    };

    std::atomic<Status> status;

    page_id_t page_id;

    data_ptr data;

    inline static DiskRequest
    New(Type type, page_id_t page_id, data_ptr data) {
        return {type, Status::Ready, page_id, data};
    }
};

}