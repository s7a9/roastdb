/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/types/type_id.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <cstdint>

namespace roastdb {

enum class TypeID : uint8_t {
    INVALID = 0, INT8, INT16, INT32, FLOAT32,
    INT64, FLOAT64, TIMESTAMP,
    CHAR, VARCHAR,
};

}