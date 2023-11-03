/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/types/tmp_any_value.hpp
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <cstring>

#include "roastdb/types/type_id.h"
#include "roastdb/types/type_utils.h"

namespace roastdb {

class TmpAnyValue {
public:
    inline
    TmpAnyValue(TypeID type, const void* src, size_t length):
        type_(type) {
        memcpy_s(&data_, sizeof(data_), src, length);
    }

    template <class ScourceType>
    inline static TmpAnyValue
    from(ScourceType src) {
        constexpr TypeID type_id = type_utils::get_type_id<ScourceType>();
        if constexpr (type_id == INVALID || type_id == Type_CHAR) {
            throw std::logic_error("TmpAnyValue::from only accept non-string scource");
        }
        return TmpAnyValue(type_id, &src, sizeof(src));
    }

    inline static TmpAnyValue
    from_string(const char* string, uint32_t size) {
        return TmpAnyValue(Type_CHAR, string, size);
    }

    template <class DestType>
    inline DestType&
    as() const {
        constexpr TypeID type_id = type_utils::get_type_id<ScourceType>();
        if (type_id != type_) {
            throw std::logic_error("TmpAnyValue::as try to cast to invalid type");
        }
        return *reinterpret_cast<DestType*>(data_);
    }

private:
    TypeID type_;

    char data_[8];
};

}