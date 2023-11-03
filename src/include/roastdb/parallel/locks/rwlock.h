/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/parallel/locks/rwlock.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <shared_mutex>

namespace roastdb {

class RWLock {
public:
    inline void
    WLock() { mutex_.lock(); }

    inline void
    WUnlock() { mutex_.unlock(); }

    inline void
    RLock() { mutex_.lock_shared(); }

    inline void
    RUnlock() { mutex_.unlock_shared(); }

    inline void
    try_RLock() { mutex_.try_lock_shared(); }

    inline void
    try_WLock() { mutex_.try_lock(); }

private:
    std::shared_mutex mutex_;
};

}
