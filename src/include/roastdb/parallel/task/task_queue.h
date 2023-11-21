/************************************************\
 *                    Roast DB
 * 
 *  src/include/roastdb/parallel/task/task_queue.h
 * 
 *  GPL-3.0 license
 * 
\*************************************************/

#pragma once

#include <queue>

#include "roastdb/parallel/locks/rwlock.h"
#include "roastdb/parallel/task/task.h"

namespace roastdb {

class TaskQueue {
public:
    TaskQueue() = default;

    ~TaskQueue() = default;

    /// @brief Push a task into the queue.
    /// @param task the task to be pushed.
    void push(Task* task);

    /// @brief Pop a task from the queue.
    /// @return the task popped.
    Task* pop();

    /// @brief Check if the queue is empty.
    /// @return true if the queue is empty, false otherwise.
    bool empty() const;

    /// @brief Get the size of the queue.
    /// @return the size of the queue.
    size_t size() const;

private:
    std::queue<Task*> queue_;

    RWLock lock_;
};

}