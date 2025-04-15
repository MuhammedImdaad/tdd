#pragma once
#include <queue>
#include <Work.h>
#include <thread>

class ThreadPool
{
    std::queue<Work> q;
    std::vector<std::thread> workerThreads;
    std::atomic<bool> done{false};
    std::mutex m;

    void job()
    {
        while (done == false)
        {
            while (hasWork())
            {
                pullWork().execute();
            }
        }
    }

    void stop()
    {
        done = true;
        for (auto& workerThread : workerThreads)
            workerThread.join();
    }

public:
    bool hasWork()
    {
        std::lock_guard<std::mutex> lock(m);
        return !q.empty();
    }
    void add(Work w)
    {
        std::lock_guard<std::mutex> lock(m);
        q.push(w);
    }

    Work pullWork()
    {
        std::lock_guard<std::mutex> lock(m);
        if (q.empty())
            return Work{};

        Work out = q.front();
        q.pop();
        return out;
    }

    void start(int numberOfThreads = 1)
    {
        for (unsigned int i{0}; i < numberOfThreads; i++)
            workerThreads.push_back(std::thread(&ThreadPool::job, this));
    }

    virtual ~ThreadPool()
    {
        stop();
    }
};