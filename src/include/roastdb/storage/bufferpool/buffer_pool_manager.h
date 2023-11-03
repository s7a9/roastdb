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

    /// @brief allocate a new page. return an invalid PageRef if unsuccessful
    /// @param access_type
    /// @return 
    PageRef new_page(bool access_type);

    /// @brief fetch a page. this will wait for disk operation when buffer miss
    /// @param page_id 
    /// @param access_type 
    /// @return 
    PageRef fetch_page(page_id_t page_id, bool access_type);

    /// @brief ask the disk manager to fetch a page.
    /// @param page_id 
    /// @return whether the disk request is posted successfully
    bool prefetch_page(page_id_t page_id);

    /// @brief mannually flush a page into disk
    /// @param page 
    /// @return whether the disk request is posted successfully
    bool flush_page(PageRef& page);

    bool delete_page(PageRef&& page);

private:
    const size_t pool_size_;

    std::atomic<page_id_t> next_page_id_{0};

    Frame *frames_;

    DiskManager* disk_manager_;

    std::unordered_map<page_id_t, frame_id_t> page_table_;

    std::list<frame_id_t> free_list_;

    std::mutex latch_;
};

}