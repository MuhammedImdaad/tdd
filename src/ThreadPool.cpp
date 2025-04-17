#include <ThreadPool.h>

void ThreadPool::job()
{
    while (!done)
    {
        while (hasWork())
        {
            pullWork().execute();
        }
    }
}

void ThreadPool::stop()
{
    done = true;
    for (auto &workerThread : workerThreads)
        if (workerThread.joinable())
            workerThread.join();

    workerThreads.clear();
}

bool ThreadPool::hasWork()
{
    std::lock_guard<std::mutex> lock(m);
    return !q.empty();
}

void ThreadPool::add(Work w)
{
    {
        std::lock_guard<std::mutex> lock(m);
        q.push(w);
    }
}

Work ThreadPool::pullWork()
{
    Work out;
    {
        std::lock_guard<std::mutex> lock(m);

        if (q.empty())
            return out;

        out = q.front();
        q.pop();
    }
    return out;
}

void ThreadPool::start(int numberOfThreads)
{
    for (unsigned int i{0}; i < numberOfThreads; i++)
        workerThreads.push_back(std::thread(&ThreadPool::job, this));
}

ThreadPool::~ThreadPool()
{
    stop();
}