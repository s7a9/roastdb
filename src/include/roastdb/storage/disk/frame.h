/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/disk/frame.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <atomic>

#include "roastdb/common/db_config.h"
#include "roastdb/parallel/locks/rwlock.h"

namespace roastdb {

class Frame {
    friend class BufferPoolManager;
    friend class PageRef;

public:
    inline
    Frame() { reset_memory_(); }

    inline data_ptr
    data() { return data_; }

    inline page_id_t
    page_id() const { return page_id_; }

    inline table_id_t
    table_id() const { return table_id_; }

    inline bool
    dirty() const { return is_dirty_; }

    inline int32_t
    pin_count() { return pin_count_.load(); }

    inline RWLock&
    lock() { return rwlock_; }

private:
    inline void
    reset_memory_() { memset(data_, 0, sizeof(data_)); }

    char data_[PAGE_SIZE];

    page_id_t page_id_{INVALID_PAGE_ID};

    table_id_t table_id_{INVALID_TABLE_ID};

    bool is_dirty_{false};

    std::atomic_int32_t pin_count_{0};

    RWLock rwlock_;
};

}