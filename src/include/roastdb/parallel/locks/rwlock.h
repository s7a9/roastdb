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

class ReadGuard {
public:
    DISALLOW_COPY(ReadGuard);

    inline
    ReadGuard(): lock_(nullptr) {}

    inline
    ReadGuard(ReadGuard&& other):
        lock_(other.lock_) { other.lock_ = nullptr; }

    inline 
    ReadGuard(RWLock& lock): lock_(&lock) { lock_->RLock(); }

    inline 
    ~ReadGuard() { if (lock_) lock_->RUnlock(); }

private:
    RWLock* lock_;
};

class WriteGuard {
public:
    DISALLOW_COPY(WriteGuard);

    inline 
    WriteGuard(): lock_(nullptr) {}

    inline 
    WriteGuard(WriteGuard&& other):
        lock_(other.lock_) { other.lock_ = nullptr; }

    inline 
    WriteGuard(RWLock& lock): lock_(&lock) { lock_->WLock(); }

    inline 
    ~WriteGuard() { if (lock_) lock_->WUnlock(); }

private:
    RWLock* lock_;
};

}
