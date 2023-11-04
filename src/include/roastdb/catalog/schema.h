/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/catalog/schema.hpp
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <vector>
#include <optional>

#include "roastdb/catalog/column_info.h"

namespace roastdb {

class Schema {
public:
    explicit Schema(const std::vector<ColumnInfo>& columns);
    
    explicit Schema(std::vector<ColumnInfo>&& columns);

    inline Schema
    select(const std::vector<uint32_t>& attrs) const {
        std::vector<ColumnInfo> cols;
        cols.reserve(attrs.size());
        for (const auto i : attrs) {
            cols.emplace_back(columns_[i]);
        }
        return Schema{std::move(cols)};
    }

    inline const std::vector<ColumnInfo>&
    columns() const { return columns_; }

    inline const ColumnInfo&
    at(uint32_t i) const { return columns_[i]; }

    uint32_t
    get_col_id(const std::string& col_name) const;

    std::optional<uint32_t>
    try_get_col_id(const std::string& col_name) const;

    inline bool
    inlined() const { return tuple_is_inlined_; }

    /// @brief get the fixed size of a tuple
    /// @return 
    inline uint32_t
    tuple_size() const { return tuple_size_; }

private:
    bool tuple_is_inlined_{true};

    uint32_t tuple_size_;

    std::vector<ColumnInfo> columns_;
};

}