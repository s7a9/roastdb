/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/common/db_condig.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <chrono>
#include <cstdint>

namespace roastdb {

std::chrono::milliseconds cycle_detection_interval;

using frame_id_t =      int32_t;
using page_id_t =       int32_t;
using txn_id_t =        int64_t;
using lsn_t =           int32_t;
using slot_offset_t =   int32_t;
using oid_t =           uint16_t;

constexpr page_id_t INVALID_PAGE_ID = -1;
constexpr frame_id_t INVALID_FRAME_ID = -1;
constexpr txn_id_t INVALID_TXN_ID = -1;
constexpr size_t BUFFER_POOL_SIZE = 256;
constexpr size_t PAGE_SIZE = 8096;
constexpr size_t BUCKET_SIZE = 64;
constexpr size_t LRUK_REPLACER_K = 10;
constexpr size_t DISK_MANAGER_WORKERS_NUM = 2;

const txn_id_t TXN_START_ID = 1145141919;

using float32_t = float;
using float64_t = double;
using timestamp_t = uint64_t;

using data_ptr = char*;

}