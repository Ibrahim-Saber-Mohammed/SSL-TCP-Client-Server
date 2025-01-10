#ifndef _THREAD_SAFETY_QUEUE__HPP__
#define _THREAD_SAFETY_QUEUE__HPP__
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
public:
    void push(T value) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(std::move(value));
        m_condVar.notify_one(); // Notify one waiting thread
    }

    bool pop(T& value) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_queue.empty()) {
            return false;
        }
        value = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

private:
    mutable std::mutex m_mutex;
    std::queue<T> m_queue;
    std::condition_variable m_condVar;
};

#endif  // _THREAD_SAFETY_QUEUE__HPP__