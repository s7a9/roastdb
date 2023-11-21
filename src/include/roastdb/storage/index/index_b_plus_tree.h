/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/index/index_b_plus_tree.hpp
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include "roastdb/storage/page/page.h"
#include "roastdb/storage/index/index.h"
#include "roastdb/storage/bufferpool/bufferpool_manager.h"

namespace roastdb {

class BPTIndexEngine : public IndexEngine {
public:
    /// @brief ScanIterator is a wrapper of node scan operation.
    class ScanIterator {};

    BPTIndexEngine(
        std::string&& name,
        table_id_t table_id,
        const Schema& table_schema,
        const std::vector<uint32_t>& key_attrs,
        BufferPoolManager& bufferpool,
        page_id_t& bpt_root_page_id
    ):  IndexEngine(
            std::move(name),
            table_id,
            table_schema,
            key_attrs,
            IndexType::BPlusTreeIndex
        ),
        bpt_root_page_id_(bpt_root_page_id),
        bufferpool_(bufferpool) {}
    
    /// @brief insert a tuple into the table
    /// @param tuple [in] has the same schema as tuples in this table
    /// @param rid [out] where the tuple is inserted
    /// @return is successful
    bool insert(const Tuple& tuple, RID& rid);

    /// @brief locate a tuple in the table
    /// @param key [in] has the same schema as key_schema
    /// @param rid [out] where is the tuple
    /// @return PageRef this page must be locked for further operation
    PageRef&& locate(const Tuple& key, RID& rid);

    /// @brief remove a tuple in the table
    /// @param key [in] has the same schema as key_schema
    /// @return is successful
    bool remove(const Tuple& key);

    /// @brief drop the table
    void drop();

    /// @brief begin scan at front
    /// @return ScanIterator
    ScanIterator begin_scan();

    /// @brief begin scan at key
    /// @param key [in]
    /// @return ScanIterator
    ScanIterator begin_scan_at(const Tuple& key);

private:
    page_id_t& bpt_root_page_id_;

    BufferPoolManager& bufferpool_;
};

}