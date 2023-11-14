/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/table/memory_table.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include "roastdb/storage/table/table.h"
#include "roastdb/storage/index/index_hashtable.h"

namespace roastdb {

/// @brief MemoryTable is a table in memory, used in nested query and hash join.
class MemoryTable : public Table {
public:
    DISALLOW_COPY(MemoryTable)
    DISALLOW_MOVE(MemoryTable)

    using Tuple = _MaterializedTuple;

    /// @brief create a table in memory
    /// @param table_id table ID
    /// @param table_name table name
    /// @param columns column info
    /// @param key_attrs primary key columns
    MemoryTable(
        table_id_t table_id,
        std::string table_name,
        const std::vector<ColumnInfo>& columns,
        const std::vector<column_id_t>& key_attrs
    ):  Table(
            TableType::Memory,
            table_id,
            std::move(table_name),
            columns
        ) {
        primary_index_ = std::make_unique<HashIndexEngine>(
            "__primary_index_" + name(),
            table_id,
            schema(),
            key_attrs
        );
    }

    inline HashIndexEngine&
    primary_index() { return primary_index_->as<HashIndexEngine>(); }

    /// TODO: add other interfaces for nested query and hash join

    inline Tuple&
    at(RID rid) { return tuples_[rid]; }

    inline const Tuple&
    at(RID rid) const { return tuples_[rid]; }

    inline RID allocate();

    void set(RID rid, column_id_t col, const Value& value);

    void remove(RID rid);

private:
    std::vector<Tuple> tuples_;

    std::vector<RID> free_rids_;
};

}