#pragma once
#include <queue>
#include <Work.h>
#include <thread>
#include <atomic>
#include <mutex>
#include <iostream>
#include <condition_variable>

class ThreadPool
{
    std::queue<Work> q;
    std::vector<std::thread> workerThreads;

    std::atomic<bool> done{false};
    std::mutex m;

    void job();
    void stop();

public:
    bool hasWork();
    virtual void add(Work w);
    Work pullWork();
    void start(int numberOfThreads = 1);
    virtual ~ThreadPool();
};