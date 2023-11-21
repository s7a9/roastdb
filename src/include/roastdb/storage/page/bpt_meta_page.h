/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/page/bpt_meta_page.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <vector>

#include "roastdb/catalog/column_info.h"
#include "roastdb/storage/page/page.h"

namespace roastdb {

/* BPTMetaPage LAYOUT
 * | Page Header | bpt root page id | 
 * | primary key num : 32 | primary key #1 : 32 | primary key #2 : 32 | ... |
 * | column num : 32 | column #1 info { type, size, name } | column #2 info | ... |
*/

/// @brief this class serves as an specalized interpreter of a bpt meta page.
/// a BPTMetaPage instance would hold PageRef in its life cycle so that the page
/// will not be unexpectedly changed by others.
class BPTMetaPage {
public:
    DISALLOW_COPY(BPTMetaPage)

    /// @brief check page type and access_type, then read data from it
    /// @param page 
    explicit BPTMetaPage(PageRef&& page);

    /// @brief must write data back to page
    ~BPTMetaPage();

    BPTMetaPage(BPTMetaPage&& other) = default;

    inline std::vector<ColumnInfo>&
    columns() { return columns_; }

    inline const std::vector<ColumnInfo>&
    columns() const { return columns_; }

    inline page_id_t&
    root_page_id() { return bpt_root_page_id_; }

    inline page_id_t
    root_page_id() const { return bpt_root_page_id_; }

    inline std::vector<uint32_t>&
    key_attrs() { return key_attrs_; }

    inline const std::vector<uint32_t>&
    key_attrs() const { return key_attrs_; }

    inline bool
    valid() const { return page_.valid(); }

private:
    PageRef page_;

    page_id_t bpt_root_page_id_;

    std::vector<ColumnInfo> columns_;

    std::vector<uint32_t> key_attrs_;
};

}