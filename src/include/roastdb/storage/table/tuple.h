/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/table/tuple.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include "roastdb/catalog/schema.h"
#include "roastdb/types/value.hpp"

namespace roastdb {

/// @brief abstract type of any tuple. provide same read operation interface
/// across all types of table.
class Tuple {
public:
    Tuple(RID rid, const Schema& schema):
        rid_(rid), schema_(schema) {}

    virtual ~Tuple() = 0;

    virtual const data_ptr
    get_at(column_id_t column_id) const = 0;

    virtual Value
    copy_at(column_id_t column_id) const = 0;

    virtual bool
    is_null(column_id_t column_id) const = 0;

    /// @brief this function is for moving the tuple ptr to another location
    /// @param rid 
    /// @return is successful
    virtual bool
    move_ptr(RID rid) = 0;

    inline RID rid() const { return rid_; }

    inline const ColumnInfo&
    col_info(column_id_t column_id) const {
        return schema_.columns()[column_id];
    }

protected:
    RID rid_;

    const Schema& schema_;
};

}