/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/table/physical_table.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include "roastdb/storage/table/table.h"
#include "roastdb/storage/index/index_b_plus_tree.h"
#include "roastdb/storage/page/bpt_meta_page.h"

namespace roastdb {

class PhysicalTable : public Table {
public:
    DISALLOW_COPY(PhysicalTable)
    DISALLOW_MOVE(PhysicalTable)

    /// @brief wrapping of how to read data from a physical table.
    /// TODO: PageRef should be BPTLeafPage
    class Tuple : public roastdb::Tuple {
    public:
        Tuple(PageRef&& page, RID rid, const Schema& schema):
            roastdb::Tuple(rid, schema), page_(std::move(page)) {}

        ~Tuple();

        const data_ptr get_at(column_id_t column_id) const;

        Value copy_at(column_id_t column_id) const;

        bool is_null(column_id_t column_id) const;

        /// @brief this function is for moving the tuple ptr to
        /// another location in one page
        /// @param rid 
        /// @return is rid exists in the same page (is successful)
        bool move_ptr(RID rid);

    private:
        PageRef page_;
    };

    /// TODO: move this funtion to cpp file
    PhysicalTable(
        table_id_t table_id,
        std::string table_name,
        BPTMetaPage&& meta_page,
        BufferPoolManager& bufferpool
    ):  Table(
            TableType::Physical,
            table_id,
            std::move(table_name),
            meta_page.columns()
        ),
        meta_page_(std::move(meta_page)) {
        // NOTE: meta_page has been moved to meta_page_
        primary_index_ = std::make_unique<BPTIndexEngine>(
            "__primary_key_" + name(),
            table_id_,
            schema(),
            meta_page_.key_attrs(),
            bufferpool,
            meta_page_.root_page_id()
        );
    }

    inline BPTIndexEngine&
    primary_index() { return primary_index_->as<BPTIndexEngine>(); }

private:
    BPTMetaPage meta_page_;
};
    
}