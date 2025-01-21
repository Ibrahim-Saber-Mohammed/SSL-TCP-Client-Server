#ifndef THREAD_SAFETY_QUEUE__HPP__
#define THREAD_SAFETY_QUEUE__HPP__
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>

namespace NETWORK{
class ThreadPool {
public:
    using TaskHandler = std::function<void(void)>;
    ThreadPool(std::size_t _numOfThreads);
    ~ThreadPool();
    void enqueue(TaskHandler _task);
private:
    mutable std::mutex m_mutex;
    std::vector<std::thread> m_workers;
    std::queue<TaskHandler> m_tasks;
    std::condition_variable m_condVar;
    bool m_stop;
    void worker(void);
};
}
#endif  // _THREAD_SAFETY_QUEUE__HPP__