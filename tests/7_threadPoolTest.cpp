#include <gtest/gtest.h>
using namespace ::testing;

#include <ThreadPool.h>
#include <chrono>
#include <unordered_set>

// [----------] 6 tests from AThreadPool
class AThreadPool : public ::Test
{
public:
    ThreadPool pool;
    std::mutex m;

    virtual ~AThreadPool() {};
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

// [----------] 3 tests from AThreadPoolExtended
class AThreadPoolExtended : public AThreadPool
{
    std::condition_variable wasExecuted;
    unsigned int count{0}; // to check if work actually gets executed

public:
    std::vector<std::thread> clients;
    void SetUp() override { pool.start(); }
    void TearDown() override
    {
        for (auto &client : clients)
            client.join();
    }

    virtual ~AThreadPoolExtended() {}

    void incrementCountAndNotify()
    {
        std::unique_lock<std::mutex> lock(m);
        ++count;
        // std::cout << "incrementCountAndNotify\n";
        wasExecuted.notify_all();
    }

    void waitForCountAndFailOnTimeout(int NumberOfWorkItems, int timeoutMilliseconds = 100)
    {
        std::unique_lock<std::mutex> lock(m);
        ASSERT_TRUE(wasExecuted.wait_for(lock, std::chrono::milliseconds(timeoutMilliseconds),
                                         [this, NumberOfWorkItems]()
                                         { return count == NumberOfWorkItems; }));
    }
};

TEST_F(AThreadPoolExtended, PullsWorkInAThread)
{
    Work work([this]()
              { incrementCountAndNotify(); });
    unsigned int NumberOfWorkItems{1};
    pool.add(work);
    waitForCountAndFailOnTimeout(NumberOfWorkItems);
}

TEST_F(AThreadPoolExtended, ExecutesAllWork)
{
    Work work([this]()
              { incrementCountAndNotify(); });
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    unsigned int NumberOfWorkItems{3};

    for (unsigned int j{0}; j < NumberOfWorkItems; j++)
        pool.add(work);
    waitForCountAndFailOnTimeout(NumberOfWorkItems);
}

TEST_F(AThreadPoolExtended, HoldsUpUnderMultiClientStress)
{
    Work work([this]()
              { incrementCountAndNotify(); });
    unsigned int NumberOfClients{30};
    unsigned int NumberOfWorkItems{30};

    for (unsigned int i{0}; i < NumberOfClients; i++)
    {
        clients.push_back(std::thread(
            [NumberOfWorkItems, &work, this]()
            {
                for (unsigned int j{0}; j < NumberOfWorkItems; j++)
                    pool.add(work);
            }));
    };

    waitForCountAndFailOnTimeout(NumberOfClients * NumberOfWorkItems, 100);
}

// [----------] 1 test from ARealThreadPool
class ARealThreadPool : public AThreadPoolExtended
{
    std::unordered_set<std::thread::id> s;

public:
    void SetUp() override {}
    void addThreadIfUnique(const std::thread::id &id)
    {
        std::unique_lock<std::mutex> lock(m);
        s.insert(id);
    };

    int numberOfThreadsProcessed() { return s.size(); };
};

TEST_F(ARealThreadPool, DispatchesWorkToMultipleThreads)
{
    int numberOfThreads{10};
    pool.start(numberOfThreads);

    Work work{
        [this]()
        {
            addThreadIfUnique(std::this_thread::get_id());
            incrementCountAndNotify();
        }};

    unsigned int NumberOfWorkItems{500};
    for (unsigned int i{0}; i < NumberOfWorkItems; i++)
        pool.add(work);

    waitForCountAndFailOnTimeout(NumberOfWorkItems);
    ASSERT_EQ(numberOfThreads, numberOfThreadsProcessed());
}