/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/catalog/catalog.hpp
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>

#include  "roastdb/storage/table/table.h"

namespace roastdb {

/// @brief A persist catalog that bookkeeps meta info of physical tables and 
/// secondary indexes. Some of the functions are non-blocking, so the caller
/// must acquire a lock guared fist.
class Catalog {
public:
    DISALLOW_COPY(Catalog)
    DISALLOW_MOVE(Catalog)

    Catalog() = default;

    ~Catalog();

    /// NOTE: this is blocking
    void put_tables(std::vector<std::unique_ptr<Table>> tables);

    /// NOTE: this is blocking
    void put_table(std::unique_ptr<Table> table);

    /// NOTE: this is blocking
    table_id_t create_table(
        std::string table_name,
        std::vector<ColumnInfo>& columns
    );

    /// NOTE: table ReadGuard needed
    Table* get_table(const std::string& name);

    /// NOTE: table ReadGuard needed
    Table* get_table(table_id_t table_id);

    /// @brief create a secondary index
    /// NOTE: index WriteGuard needed
    IndexEngine* create_index(
        Table* table,
        const std::string& index_name,
        const std::vector<column_id_t>& key_attrs
    );

    /// NOTE: index ReadGuard needed
    IndexEngine* get_index(const std::string index_name);

    /// NOTE: index ReadGuard needed
    IndexEngine* get_index(index_id_t index_id);

    /// @brief All indexes of a table, primary included.
    /// NOTE: index ReadGuard needed
    /// @param table 
    /// @return empty if table not exist
    std::vector<IndexEngine*>
    get_indexes_of_table(Table* table);

    /// @brief remove the table from catalog.
    /// NOTE: index AND table WriteGuard needed
    /// @param table 
    /// @return owning pointer to table for further cleanup
    std::unique_ptr<Table> remove_table(Table* table);

    /// @brief remove a secondary index from catalog.
    /// NOTE: index WriteGuard needed
    /// @param index 
    /// @return whether the index exists
    bool remove_index(IndexEngine* index);

    inline RWLock& table_lock() { return table_lock_; }

    inline RWLock& index_lock() { return index_lock_; }

private:
    std::unordered_map<table_id_t, std::unique_ptr<Table>> tables_;

    std::unordered_map<std::string, table_id_t> name2tableid_;

    /// @brief protects tables_ and name2tableid_
    RWLock table_lock_;

    std::unordered_map<index_id_t, std::unique_ptr<IndexEngine>> indexes_;

    std::unordered_map<std::string, index_id_t> name2indexid_;

    /// @brief protects indexes_ and name2indexid_
    RWLock index_lock_;
};

}