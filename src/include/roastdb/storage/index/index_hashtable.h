/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/index/index_hashtable.hpp
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <unordered_map>

#include "roastdb/storage/index/index.h"

namespace roastdb {

/// @brief HashIndexEngine manages how to look up tuple in a table by hashtable.
/// Currently this utilizes a mutex to protect the hashtable, we may change this 
/// to use lock-free hashtable in the future.
/// Note that if this is a secondary index belongs to a Physical Table,
/// you must fetch the page manually and synchronize changes with primary index.
class HashIndexEngine : public IndexEngine {
public:
    HashIndexEngine(
        std::string&& name,
        table_id_t table_id,
        const Schema& table_schema,
        const std::vector<uint32_t>& key_attrs
    ):  IndexEngine(
            std::move(name),
            table_id,
            table_schema,
            key_attrs,
            IndexType::HashTableIndex
        ) {}
    
    /// @brief insert a tuple into the table.
    /// @param tuple [in] has the same schema as tuples in this table
    /// @param rid [out] where the tuple is inserted
    /// @return is successful
    bool insert(const Tuple& tuple, RID& rid);

    /// @brief locate a tuple in the table
    /// @param key [in] has the same schema as key_schema
    /// @param rid [out] where is the tuple
    /// @return whether this tuple exists
    bool locate(const Tuple& key, RID& rid);

    /// @brief remove a tuple in the table
    /// @param key [in] has the same schema as key_schema
    /// @return rid of tuple to be removed
    RID remove(const Tuple& key);

private:
    std::unordered_map<hash_t, RID> hashtable_;
};

}