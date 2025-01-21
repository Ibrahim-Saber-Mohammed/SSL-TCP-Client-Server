#include <server/ThreadPool.hpp>

namespace NETWORK{
ThreadPool::ThreadPool(std::size_t _numOfThreads) : m_stop(false)
{
    for(int iter{0}; iter < _numOfThreads; iter++)
    {
        m_workers.emplace_back(&ThreadPool::worker, this);
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_stop = true;
    } 
    m_condVar.notify_all();
    for(auto &workerthread: m_workers)
    {
        if(workerthread.joinable())
        {
            workerthread.join();
        }
    }
}
void ThreadPool::enqueue(TaskHandler _task)
{
    { 
        std::unique_lock<std::mutex> lock(m_mutex);
        m_tasks.push(std::move(_task));
    } 
    m_condVar.notify_one();
}
void ThreadPool::worker()
{
    while (true)
    {
        TaskHandler task;
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_condVar.wait(lock, [this]() { return m_stop || !m_tasks.empty(); });
            if (m_stop && m_tasks.empty())
                return;
            task = std::move(m_tasks.front());
            m_tasks.pop();
        }
        task();
    }
}
}