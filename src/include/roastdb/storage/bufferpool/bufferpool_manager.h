/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/bufferpool/buffer_pool_manager.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <list>
#include <mutex>
#include <memory>
#include <vector>
#include <unordered_map>

#include "roastdb/storage/page/page.h"
#include "roastdb/storage/disk/disk_manager.h"

namespace roastdb {

class BufferPoolManager {
public:
    BufferPoolManager(
        size_t pool_size,
        DiskManager* disk_manager,
        size_t replacer_k = LRUK_REPLACER_K
    );

    ~BufferPoolManager();

    inline size_t
    pool_size() const { return pool_size_; }

    bool open_table_file(table_id_t table_id, const std::string& filename);

    bool close_table_file(table_id_t table_id);

    /// @brief allocate a new page. return an invalid PageRef if unsuccessful
    /// @param access_type
    /// @return 
    PageRef new_page(table_id_t table_id, bool access_type);

    /// @brief fetch a page. this will wait for disk operation when buffer miss
    /// @param page_id 
    /// @param access_type 
    /// @return 
    PageRef fetch_page(table_id_t table_id, page_id_t page_id, bool access_type);

    /// @brief ask the disk manager to fetch a page.
    /// @param page_id 
    /// @return the disk request, you can check its status
    std::shared_ptr<DiskRequest> prefetch_page(table_id_t table_id, page_id_t page_id);

    /// @brief manually flush a page into disk
    /// @param page 
    /// @return the disk request, you can check its status
    std::shared_ptr<DiskRequest> flush_page(PageRef& page);

    bool delete_page(PageRef&& page);

private:
    const size_t pool_size_;

    std::atomic<page_id_t> next_page_id_{0};

    Frame *frames_;

    std::unordered_map<table_id_t, std::unique_ptr<DiskManager>> disk_managers_;

    std::unordered_map<page_id_t, frame_id_t> page_table_;

    std::list<frame_id_t> free_list_;

    std::mutex latch_;
};

}