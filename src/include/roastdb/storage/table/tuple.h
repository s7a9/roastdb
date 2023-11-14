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

    virtual hash_t
    hash_at(column_id_t column_id) const = 0;

    virtual bool
    is_null(column_id_t column_id) const = 0;

    /// @brief this function is for moving the tuple ptr to another location
    /// @param rid 
    /// @return is successful
    virtual bool move_ptr(RID rid) = 0;

    inline RID rid() const { return rid_; }

    inline const ColumnInfo&
    col_info(column_id_t column_id) const {
        return schema_.columns()[column_id];
    }

protected:
    RID rid_;

    const Schema& schema_;
};

/// @brief The actual tuple stored in memory. Note that this class
/// stores data in itself, not like others which are references.
class _MaterializedTuple : public Tuple {
public:
    DISALLOW_COPY(_MaterializedTuple)

    /// @brief reserve space for a tuple
    /// @param rid 
    /// @param schema 
    _MaterializedTuple(RID rid, const Schema& schema);

    _MaterializedTuple(_MaterializedTuple&& other);

    ~_MaterializedTuple();

    _MaterializedTuple&
    operator=(_MaterializedTuple&& other);

    /// @brief get the raw pointer at the column
    /// @param column_id 
    /// @return data poisnter
    const data_ptr get_at(column_id_t column_id) const;

    /// @brief copy the value
    /// @param column_id 
    /// @return value
    Value copy_at(column_id_t column_id) const;

    bool is_null(column_id_t column_id) const;

    /// @brief get the hash value of the column
    /// @param column_id 
    /// @return hash value
    hash_t hash_at(column_id_t column_id) const;

    /// @brief this function is for moving the tuple ptr to
    /// another location in one page
    /// @param rid 
    /// @return is rid exists in the same page (is successful)
    bool move_ptr(RID rid);

    /// @brief set the value at the column
    /// @param column_id 
    /// @param value 
    void set_at(column_id_t column_id, const Value& value);

    /// @brief set the tuple as removed
    void remove();

private:
    bool is_removed_;

    std::vector<Value> values_;

    std::vector<data_ptr> varchars_;
};

}