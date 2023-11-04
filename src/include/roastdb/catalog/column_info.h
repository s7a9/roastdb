/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/catalog/column_info.hpp
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <string>

#include "roastdb/types/type_id.h"
#include "roastdb/types/type_utils.h"

namespace roastdb {

/// @brief `ColumnInfo` stores the location of a certain column in tuple.
class ColumnInfo {
    friend class Schema;

public:
    /// @brief Non-variable-length constructor for creating a Column.
    /// @param column_name 
    /// @param type
    ColumnInfo(std::string column_name, TypeID type):
        column_name_(std::move(column_name)),
        column_type_(type),
        column_size_(type_utils::get_type_size(type)) {
        ROASTDB_ASSERT(
            type != TypeID::VARCHAR && type != TypeID::CHAR,
            "Wrong constructor for VARCHAR type."
        );
    }

    /// @brief Variable-length constructor for creating a Column.
    /// @param column_name 
    /// @param type 
    /// @param var_size Size of the pointer
    ColumnInfo(std::string column_name, TypeID type, uint32_t var_size):
        column_name_(std::move(column_name)),
        column_type_(type),
        column_size_(var_size) {
        ROASTDB_ASSERT(
            type == TypeID::VARCHAR || type == TypeID::CHAR,
            "Wrong constructor for non-VARCHAR type."
        );
    }

    /// @brief Replicate a columninfo with a different name.
    /// @param column_name 
    /// @param other 
    ColumnInfo(std::string column_name, const ColumnInfo& other):
        column_name_(std::move(column_name)),
        column_type_(other.column_type_),
        column_size_(other.column_size_),
        column_offset_(other.column_offset_) {}

    /// @brief deserialize from bytes
    /// @param col_data 
    ColumnInfo(const data_ptr col_data);
    
    inline TypeID
    type() const { return column_type_; }

    inline bool
    inlined() const { return column_type_ != TypeID::VARCHAR; }

    inline uint32_t
    offset() const { return column_offset_; }

    inline uint32_t
    size() const { return column_size_; }

    inline const std::string&
    name() const { return column_name_; }

    static constexpr size_t SERIALIZE_SIZE = (sizeof(TypeID) + sizeof(uint32_t) + NAME_LENGTH_MAX);

    inline void serialize(data_ptr to) const; 

private:
    std::string column_name_;

    TypeID column_type_;

    /// @brief For a non-inlined column in a physical table, this attribute
    /// is the size of a pointer.
    uint32_t column_size_;

    uint32_t column_offset_{0};
};

}