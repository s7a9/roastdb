/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/types/value.hpp
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <cstring>

#include "roastdb/types/type_id.h"
#include "roastdb/types/type_utils.h"

namespace roastdb {

class Value {
public:
    Value(const Value& other);

    Value(Value&& other):
        type_(other.type_) {
        memcpy(data_, other.data_, sizeof(data_));
        other.type_ = TypeID::INVALID;
        memset(other.data_, 0, sizeof(data_));
    }

    inline
    Value(TypeID type, const void* src, size_t length):
        type_(type) {
        memcpy_s(&data_, sizeof(data_), src, length);
    }

    template <class ScourceType>
    inline static Value
    from(ScourceType src) {
        constexpr TypeID type_id = type_utils::get_type_id<ScourceType>();
        if constexpr (type_id == TypeID::INVALID || type_id == TypeID::CHAR) {
            throw std::logic_error("Value::from only accept non-string scource");
        }
        return Value(type_id, &src, sizeof(src));
    }

    inline static Value
    from_string(const char* string, uint32_t size) {
        char* copy_str = new char[size + 1];
        memcpy_s(copy_str, size, string, size);
        copy_str[size] = '\0';
        return Value(TypeID::CHAR, copy_str, sizeof(char*));
    }

    template <class DestType>
    inline DestType&
    as() const {
        constexpr TypeID type_id = type_utils::get_type_id<ScourceType>();
        if (type_id != type_) {
            throw std::logic_error("Value::as try to cast to wrong type");
        }
        return *reinterpret_cast<DestType*>(data_);
    }

    Value&
    operator=(Value&& other) {
        if (this == &other) return *this;
        release_();
        type_ = other.type_;
        memcpy(data_, other.data_, sizeof(data_));
        other.type_ = TypeID::INVALID;
        memset(other.data_, 0, sizeof(data_));
    }

    Value&
    operator=(const Value& other);

    inline ~Value() { release_(); }

private:
    inline void release_() {
        if (type_ == TypeID::CHAR) {
            delete[] as<char*>();
        }
    }

    TypeID type_;

    char data_[8];
};

}