#pragma once

class Work
{
    int workId;
    std::function<void()> func;

public:
    Work(int workId = 0)
        : workId{workId}, func{[]() {}}
    {
    }

    Work(std::function<void()> func, int workId = 0)
        : func(func), workId(workId)
    {
    }

    auto execute()
    {
        func();
    }

    int id()
    {
        return workId;
    }
};