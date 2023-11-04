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

using table_id_t    = uint32_t;
using column_id_t   = uint32_t;
using slot_id_t     = uint32_t;
using index_id_t    = uint32_t;
using frame_id_t    = int32_t;
using page_id_t     = int32_t;
using txn_id_t      = int64_t;
using lsn_t         = int32_t;
using slot_offset_t = int32_t;
using oid_t         = uint16_t;
using index_id_t    = int32_t;

/// @brief the universial record identifier
using RID = uint64_t;
/* format for Physical table |32bits page_id|32bits slot_id|
*  format for others: directly the index in memory */

constexpr page_id_t INVALID_PAGE_ID = -1;
constexpr frame_id_t INVALID_FRAME_ID = -1;
constexpr table_id_t INVALID_TABLE_ID = 0; // table id starts from 1
constexpr txn_id_t INVALID_TXN_ID = -1;
constexpr index_id_t INVALID_INDEX_ID = -1;
constexpr size_t BUFFER_POOL_SIZE = 256;
constexpr RID INVALID_RID = (RID)INVALID_PAGE_ID << 32;
constexpr size_t PAGE_SIZE = 8196;
constexpr size_t BUCKET_SIZE = 64;
constexpr size_t LRUK_REPLACER_K = 10;
constexpr size_t DISK_MANAGER_WORKERS_NUM = 2;

// this restricts the length of table names and column names.
// this length includes the 0 terminate byte
constexpr size_t NAME_LENGTH_MAX = 25; 

const txn_id_t TXN_START_ID = 1145141919;

using float32_t = float;
using float64_t = double;
using timestamp_t = uint64_t;

using data_ptr = char*;

}