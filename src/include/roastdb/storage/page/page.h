/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/storage/page/page.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <cstdint>

#include "roastdb/common/macros.h"
#include "roastdb/storage/disk/frame.h"

namespace roastdb {

/* 
 * PAGE LAYOUT
 * | HEADER {page_type} | DATA |
*/

enum class PageType : uint8_t {
    Empty = 0, BPTMeta, BPTNode, BPTLeaf, Invalid = -1,
};

struct PageMeta {
    PageType type;
};

/// @brief `PageRef` is a reference to a frame in memory, which helps automatically
/// manage pin count and rwlock.
class PageRef {
public:
    static constexpr size_t HEADER_SIZE = sizeof(PageMeta);

    static constexpr bool READ = false, WRITE = true;

    DISALLOW_COPY(PageRef)

    PageRef():
        frame_id_(INVALID_FRAME_ID),
        access_type_(READ),
        frame_(nullptr) {}

    PageRef(bool access_type, Frame& frame, frame_id_t frame_id):
        access_type_(access_type),
        frame_id_(frame_id),
        frame_(&frame) {
        ++frame_->pin_count_;
        if (access_type_ == WRITE) {
            frame.lock().WLock();
        }
        else {
            frame.lock().RLock();
        }
    }

    PageRef(PageRef&& other):
        access_type_(other.access_type_),
        frame_id_(other.frame_id_),
        frame_(other.frame_) {
        other.frame_ = nullptr;
        other.frame_id_ = INVALID_FRAME_ID;
    }

    inline PageRef&
    operator=(PageRef&& other) {
        if (this == &other) return *this;
        free_ref_();
        access_type_ = other.access_type_;
        frame_id_ = other.frame_id_;
        frame_ = other.frame_;
        other.frame_ = nullptr;
        other.frame_id_ = INVALID_FRAME_ID;
    }

    ~PageRef() { free_ref_(); }

    inline bool
    valid() const { return frame_ != nullptr; }

    inline table_id_t
    table_id() const { return valid() ? frame_->table_id() : INVALID_TABLE_ID; }

    inline page_id_t
    page_id() const { return valid() ? frame_->page_id() : INVALID_PAGE_ID; }

    inline page_id_t
    frame_id() const { return frame_id_; }

    inline const data_ptr
    read_data() const {
        if (!valid()) return nullptr;
        return frame_->data() + HEADER_SIZE;
    }

    /// @brief NOTE: when this function is called, the frame will be dirty
    /// @return 
    inline data_ptr
    write_data() {
        if (!valid()) return nullptr;
        if (!access_type_) {
            throw std::logic_error("write to a read-only PageRef");
        }
        frame_->is_dirty_ = true;
        return frame_->data() + HEADER_SIZE;
    }

    inline PageMeta*
    meta() { 
        if (!valid()) return nullptr;
        return reinterpret_cast<PageMeta*>(frame_->data());
    }

    inline const PageMeta*
    meta() const { 
        if (!valid()) return nullptr;
        return reinterpret_cast<const PageMeta*>(frame_->data());
    }

    inline void
    release() { 
        free_ref_();
        frame_ = nullptr;
    }

private:
    inline void free_ref_() {
        if (!valid()) return;
        --frame_->pin_count_;
        if (access_type_ == WRITE) {
            frame_->lock().WUnlock();
        }
        else {
            frame_->lock().RUnlock();
        }
    }

    bool access_type_;

    frame_id_t frame_id_;

    Frame* frame_;
};

}