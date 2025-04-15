#include <gtest/gtest.h>
using namespace ::testing;

#include <ThreadPool.h>

class AThreadPool : public ::Test
{
    public:
    ThreadPool pool;
};

TEST_F(AThreadPool, HasNoWorkOnCreation) {
    ASSERT_FALSE(pool.hasWork());
 }
 
 TEST_F(AThreadPool, HasWorkAfterAdd) {
    pool.add(Work{});
 
    ASSERT_TRUE(pool.hasWork());
 }
 
 TEST_F(AThreadPool, AnswersWorkAddedOnPull) {
    pool.add(Work{1});
 
    auto work = pool.pullWork();
 
    ASSERT_EQ(1, work.id());
 }
 
 TEST_F(AThreadPool, PullsElementsInFIFOOrder) {
    pool.add(Work{1});
    pool.add(Work{2});
 
    auto work = pool.pullWork();
    ASSERT_EQ(1, work.id());
 }
 
 TEST_F(AThreadPool, HasNoWorkAfterLastElementRemoved) {
    pool.add(Work{});
 
    pool.pullWork();
 
    ASSERT_FALSE(pool.hasWork());
 }
 
 TEST_F(AThreadPool, HasWorkAfterWorkRemovedButWorkRemains) {
    pool.add(Work{});
    pool.add(Work{});
 
    pool.pullWork();
 
    ASSERT_TRUE(pool.hasWork());
 }