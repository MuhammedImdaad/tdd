#include <gtest/gtest.h>
using namespace ::testing;

#include <ThreadPool.h>
#include <chrono>

class AThreadPool : public ::Test
{
public:
    ThreadPool pool;
    std::mutex m;

    virtual ~AThreadPool() {};
};

class AThreadPoolExtended : public AThreadPool
{
    std::condition_variable wasExecuted;
    unsigned int count{0}; // to check if work actually gets executed
public:
    void SetUp() { pool.start(); }

    Work work{[&]
              {
                  std::unique_lock<std::mutex> lock(m);
                  ++count;
                  wasExecuted.notify_all();
              }};

    void waitForCountAndFailOnTimeout(int NumberOfWorkItems)
    {
        std::unique_lock<std::mutex> lock(m);
        ASSERT_TRUE(wasExecuted.wait_for(lock, std::chrono::milliseconds(100), [&]()
                                         { return count == NumberOfWorkItems; }));
    }
};

TEST_F(AThreadPool, HasNoWorkOnCreation)
{
    ASSERT_FALSE(pool.hasWork());
}

TEST_F(AThreadPool, HasWorkAfterAdd)
{
    pool.add(Work{});

    ASSERT_TRUE(pool.hasWork());
}

TEST_F(AThreadPool, AnswersWorkAddedOnPull)
{
    pool.add(Work{1});

    auto work = pool.pullWork();

    ASSERT_EQ(1, work.id());
}

TEST_F(AThreadPool, PullsElementsInFIFOOrder)
{
    pool.add(Work{1});
    pool.add(Work{2});

    auto work = pool.pullWork();
    ASSERT_EQ(1, work.id());
}

TEST_F(AThreadPool, HasNoWorkAfterLastElementRemoved)
{
    pool.add(Work{});

    pool.pullWork();

    ASSERT_FALSE(pool.hasWork());
}

TEST_F(AThreadPool, HasWorkAfterWorkRemovedButWorkRemains)
{
    pool.add(Work{});
    pool.add(Work{});

    pool.pullWork();

    ASSERT_TRUE(pool.hasWork());
}

TEST_F(AThreadPoolExtended, PullsWorkInAThread)
{
    unsigned int NumberOfWorkItems{1};
    pool.add(work);
    waitForCountAndFailOnTimeout(NumberOfWorkItems);
}

TEST_F(AThreadPoolExtended, ExecutesAllWork)
{
    // std::this_thread::sleep_for(std::chrono::microseconds(1));
    unsigned int NumberOfWorkItems{3};

    for (unsigned int i{0}; i < NumberOfWorkItems; i++)
        pool.add(work);
    waitForCountAndFailOnTimeout(NumberOfWorkItems);
}