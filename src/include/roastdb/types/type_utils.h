/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/types/type_utils.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include "roastdb/common/macros.h"
#include "roastdb/common/db_config.h"
#include "roastdb/types/type_id.h"

namespace roastdb {

namespace type_utils {

inline uint32_t
get_type_size(TypeID type_id);

template <class ScourceType>
inline constexpr TypeID
get_type_id() { return INVALID; }

template <>
inline constexpr TypeID
get_type_id<int8_t>() { return TypeID::INT8; }

template <>
inline constexpr TypeID
get_type_id<int16_t>() { return TypeID::INT16; }

template <>
inline constexpr TypeID
get_type_id<int32_t>() { return TypeID::INT32; }

template <>
inline constexpr TypeID
get_type_id<int64_t>() { return TypeID::INT64; }

template <>
inline constexpr TypeID
get_type_id<float32_t>() { return TypeID::FLOAT32; }

template <>
inline constexpr TypeID
get_type_id<float64_t>() { return TypeID::FLOAT64; }

template <>
inline constexpr TypeID
get_type_id<timestamp_t>() { return TypeID::TIMESTAMP; }

template <>
inline constexpr TypeID
get_type_id<char*>() { return TypeID::CHAR; }

}

}