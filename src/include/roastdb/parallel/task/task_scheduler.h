/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/parallel/task/task_scheduler.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <mutex>
#include <thread>
#include <unordered_map>
#include <condition_variable>

#include "roastdb/common/db_config.h"
#include "roastdb/parallel/task/task_queue.h"

namespace roastdb {

/// @brief TaskScheduler is a scheduler for tasks.
class TaskScheduler {
public:
    TaskScheduler(int thread_count);

    ~TaskScheduler() { shutdown(); }

    void schedule(Task* task);

    void schedule(const std::vector<Task*>& tasks);

    void shutdown();

private:
    /// @brief The main function of a worker thread.
    /// It will infinitely pop tasks from the queue and execute them
    /// (or stall if there is no task in the queue),
    /// until the scheduler is shutdown.
    void versatile_worker();

    bool has_shutdown_ = false;

    std::atomic<uint32_t> idle_thread_count_ = 0;

    std::unordered_map<table_id_t, TaskQueue> table_queues_; 

    std::mutex mutex_;

    std::condition_variable cv_;

    std::vector<std::thread> threads_;
};

}