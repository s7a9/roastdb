/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/index/index_multi_hashtable.hpp
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <unordered_map>

#include "roastdb/storage/index/index.h"

namespace roastdb {

/// @brief HashIndexEngine manages how to look up tuple in a table by multi-hashtable.
/// This is only used for secondary index and use a mutex to protect the hashtable.
class MultiHashIndexEngine : public IndexEngine {
public:
    MultiHashIndexEngine(
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

    /// @brief insert a tuple into the table
    /// @param tuple [in] has the same schema as tuples in this table
    /// @param rid [out] where the tuple is inserted
    /// @return is successful
    bool insert(const Tuple& tuple, RID& rid);

    /// @brief locate a tuple in the table
    /// @param key [in] has the same schema as key_schema
    /// @return tuple rids found
    std::vector<RID> locate(const Tuple& key);

    /// @brief remove a tuple in the table
    /// @param key [in]
    /// @param rid [in]
    /// @return is successful
    bool remove(const Tuple& key, RID rid);

private:
    std::unordered_multimap<hash_t, RID> hashtable_;
};

}