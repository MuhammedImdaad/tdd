#pragma once
#include <queue>
#include <Work.h>

class ThreadPool
{
    std::queue<Work> q;

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
};