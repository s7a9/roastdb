/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/index/index.hpp
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <string>

#include "roastdb/common/db_config.h"
#include "roastdb/catalog/schema.h"
#include "roastdb/storage/table/tuple.h"
#include "roastdb/parallel/locks/rwlock.h"

namespace roastdb {

enum class IndexType : uint8_t {
    BPlusTreeIndex,         // index for physical table
    HashTableIndex,         // index for secondary table and other in-memory table
    MultiHashTableIndex,    // same as HashTableIndex but allow multi-keys
    VectorIndex,            // index for vector table
};

/// @brief IndexEngine manages how to look up tuple in a table.
/// Its api is universial across different keys.
class IndexEngine {
public:
    /// @brief construct an Index
    /// @param name index name
    /// @param table_id
    /// @param table_schema 
    /// @param key_attrs mark which columns are the keys
    /// @param index_type 
    inline IndexEngine(
        std::string&& name,
        table_id_t table_id,
        const Schema& table_schema,
        const std::vector<uint32_t>& key_attrs,
        IndexType index_type
    ):  index_type_(index_type),
        table_id_(table_id),
        table_schema_(table_schema),
        index_name_(name),
        key_schema_(table_schema.select(key_attrs)),
        key_attrs_(key_attrs){}

    inline const std::string&
    name() const { return index_name_; }

    inline table_id_t
    table_id() const { return table_id_; }

    inline uint32_t
    index_col_count() const { return static_cast<uint32_t>(key_attrs_.size()); }

    inline const std::vector<uint32_t>&
    key_attrs() const { return key_attrs_; }

    inline bool
    is_primary_key() const { return index_type_ == IndexType::BPlusTreeIndex; }

    inline IndexType
    type() const { return index_type_; }

    template <class IndexDerive>
    inline IndexDerive&
    as() { return reinterpret_cast<IndexDerive&>(*this); }

    template <class IndexDerive>
    inline const IndexDerive&
    as() const { return reinterpret_cast<const IndexDerive&>(*this); }

    inline RWLock& lock() { return lock_; }

protected:
    inline const Schema&
    key_schema() const { return key_schema_; }

    RWLock lock_;

    IndexType index_type_;
    
    table_id_t table_id_;

    const Schema& table_schema_;

    std::string index_name_;

    Schema key_schema_;
    
    /// @brief corresponding col_id in the original table
    std::vector<uint32_t> key_attrs_;
};

}