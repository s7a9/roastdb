/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/table/table.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <string>
#include <memory>
#include <cstdint>

#include "roastdb/catalog/schema.h"
#include "roastdb/storage/index/index.h"

namespace roastdb {

enum class TableType : uint8_t {
    Invalid, 
    Physical,  // the table is on the disk
    Memory,    // the table is in memory and with index for nested query
    Vector,    // the table is temporary, only list of tuples
};

/// @brief Base type of any table in our databse.
class Table {
public:
    DISALLOW_COPY(Table)
    DISALLOW_MOVE(Table)

    Table(
        TableType table_type,
        table_id_t table_id,
        std::string table_name,
        const std::vector<ColumnInfo>& columns
    ):  table_type_(table_type),
        table_id_(table_id),
        table_name_(std::move(table_name)),
        schema_(columns) {}

    inline TableType
    type() const { return table_type_; }

    inline table_id_t
    table_id() const { return table_id_; }

    inline const std::string&
    name() const { return table_name_; }

    inline const Schema&
    schema() const { return schema_; }

    inline const IndexEngine&
    primary_index() const { return *primary_index_; }

    inline RWLock&
    lock() { return rwlock_; }

protected:
    TableType table_type_;

    table_id_t table_id_;

    std::string table_name_;

    Schema schema_;

    std::unique_ptr<IndexEngine> primary_index_;

    RWLock rwlock_;
};

}