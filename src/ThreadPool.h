#pragma once
#include <queue>
#include <Work.h>
#include <thread>

class ThreadPool
{
    std::queue<Work> q;
    std::unique_ptr<std::thread> workerThread = nullptr;
    std::atomic<bool> done{false};

    void job()
    {
        while (!done && hasWork())
        {
            pullWork().execute();
        }
    }

    void stop()
    {
        done = true;
        if (workerThread)
            workerThread->join();
    }

public:
    bool hasWork() { return !q.empty(); }
    void add(Work w) { q.push(w); }
    Work pullWork()
    {
        Work out;
        if (hasWork())
        {
            out = q.front();
            q.pop();
        }
        return out;
    }

    void start()
    {
        workerThread = std::make_unique<std::thread>(&ThreadPool::job, this);
    }

    virtual ~ThreadPool()
    {
        stop();
    }
};