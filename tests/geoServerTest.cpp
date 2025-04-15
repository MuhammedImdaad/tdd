#include <gtest/gtest.h>
#include <GeoServer.h>
#include <Location.h>
#include <ThreadPool.h>
#include <future>

using namespace testing;

class AGeoServer : public Test
{
public:
    std::string user = "user1";
    GeoServer server;
};

TEST_F(AGeoServer, TracksAUser)
{
    server.track(user);
    ASSERT_TRUE(server.isTracking(user));
}

TEST_F(AGeoServer, IsNotTrackingAUserNotTracked)
{
    ASSERT_FALSE(server.isTracking(user));
}

TEST_F(AGeoServer, TracksMultipleUsers)
{
    server.track(user);
    server.track("anotheruser");
    ASSERT_FALSE(server.isTracking("thirduser"));
    ASSERT_TRUE(server.isTracking(user));
    ASSERT_TRUE(server.isTracking("anotheruser"));
}

TEST_F(AGeoServer, IsTrackingAnswersFalseWhenUserNoLongerTracked)
{
    server.track(user);
    server.stopTracking(user);
    ASSERT_FALSE(server.isTracking(user));
}

TEST_F(AGeoServer, UpdatesLocationOfUser)
{
    server.track(user);
    server.updateLocation(user, Location{38, -104});

    auto location = server.locationOf(user);
    ASSERT_DOUBLE_EQ(38, location.latitude());
    ASSERT_DOUBLE_EQ(-104, location.longitude());
}

TEST_F(AGeoServer, AnswersUnknownLocationForUserNotTracked)
{
    ASSERT_TRUE(server.locationOf("anAbUser").isUnknown());
}

TEST_F(AGeoServer, AnswersUnknownLocationForTrackedUserWithNoLocationUpdate)
{
    server.track(user);
    ASSERT_TRUE(server.locationOf(user).isUnknown());
}

TEST_F(AGeoServer, AnswersUnknownLocationForUserNoLongerTracked)
{
    server.track(user);
    server.updateLocation(user, Location(40, 100));
    server.stopTracking(user);
    ASSERT_TRUE(server.locationOf(user).isUnknown());
}

TEST_F(AGeoServer, UpdatesLocationOfUserByAnotherUser)
{
    server.track(user);
    server.updateLocation(user, Location{38, -104});

    std::string user2 = "AnotherUser";
    const double TenMeters{10};
    const double Width{2000 + TenMeters};

    server.track(user2);
    server.updateLocation(user2, server.locationOf(user).go(Width / 2 - TenMeters, East));

    auto location = server.locationOf(user2);
    ASSERT_NEAR(38, location.latitude(), 0.015);
    ASSERT_NEAR(-104, location.longitude(), 0.015);
}

class AGeoServer_UsersInBox : public Test
{
public:
    GeoServer server;

    const double TenMeters{10};

    const double Width{2000 + TenMeters};

    const double Height{4000 + TenMeters};

    const std::string aUser{"auser"};

    const std::string bUser{"buser"};

    const std::string cUser{"cuser"};

    Location aUserLocation{38, -103};

    virtual void SetUp() override
    {
        pool = std::make_unique<SingleThreadedPool>();
        server.useThreadPool(pool);
        trackingListener = std::make_shared<GeoServerUserTrackingListener>();
        server.track(aUser);
        server.track(bUser);
        server.track(cUser);
        server.updateLocation(aUser, aUserLocation);
    }

    std::vector<std::string> UserNames(const std::vector<User> &users)
    {
        std::vector<std::string> result;
        for (const auto &each : users)
        {
            result.push_back(each.name());
        }
        return result;
    }

    void addUsersAt(unsigned int number, const Location &location)
    {
        for (unsigned int i{0}; i < number; i++)
        {
            std::string user{"user" + std::to_string(i)};
            server.track(user);
            server.updateLocation(user, location);
        }
    }

    class GeoServerUserTrackingListener : public GeoServerListner
    {
    public:
        std::vector<User> trackedUsers;
        virtual void updated(const User &user) override
        {
            trackedUsers.push_back(user);
        }
    };

    class SingleThreadedPool : public ThreadPool
    {
    public:
        virtual void add(Work w) override
        {
            w.execute();
        }
    };

    std::unique_ptr<ThreadPool> pool;
    std::shared_ptr<GeoServerListner> trackingListener;
};

TEST_F(AGeoServer_UsersInBox, AnswersUsersInSpecifiedRange)
{
    server.startThreads(0);

    server.updateLocation(
        bUser, Location{aUserLocation.go(Width / 2 - TenMeters, East)});
    server.usersInBox(aUser, Width, Height, trackingListener);

    ASSERT_EQ(std::vector<std::string>{bUser}, UserNames(std::static_pointer_cast<GeoServerUserTrackingListener>(trackingListener)->trackedUsers));
}

TEST_F(AGeoServer_UsersInBox, AnswersOnlyUsersWithinSpecifiedRange)
{
    server.startThreads(0);

    server.updateLocation(
        bUser, Location{aUserLocation.go(Width / 2 + TenMeters, East)});

    server.updateLocation(
        cUser, Location{aUserLocation.go(Width / 2 - TenMeters, East)});

    server.usersInBox(aUser, Width, Height, trackingListener);

    ASSERT_EQ(std::vector<std::string>{cUser}, UserNames(std::static_pointer_cast<GeoServerUserTrackingListener>(trackingListener)->trackedUsers));
}

TEST_F(AGeoServer_UsersInBox, HandlesLargeNumbersOfUsers)
{
    server.startThreads(0);

    const unsigned int lots{500000};
    addUsersAt(lots, Location{aUserLocation.go(TenMeters, West)});

    server.usersInBox(aUser, Width, Height, trackingListener);

    ASSERT_EQ(lots, std::static_pointer_cast<GeoServerUserTrackingListener>(trackingListener)->trackedUsers.size());
}

class AGeoServer_ScaleTests : public AGeoServer_UsersInBox
{
public:
    virtual void SetUp() override
    {
        pool = std::make_unique<ThreadPool>();
        trackingListener = std::make_shared<GeoServerScaleListener>();
        server.useThreadPool(pool);
        server.track(aUser);
        server.updateLocation(aUser, aUserLocation);
    }

    class GeoServerScaleListener : public GeoServerListner
    {
        std::mutex m;
        unsigned int count{0}; // to check if work actually gets executed
        std::condition_variable wasExecuted;

        void incrementCountAndNotify()
        {
            std::unique_lock<std::mutex> lock(m);
            ++count;
            wasExecuted.notify_all();
        }

    public:
        virtual void updated(const User &user) override
        {
            incrementCountAndNotify();
        }

        void waitForCountAndFailOnTimeout(int NumberOfWorkItems, int timeoutMilliseconds = 100)
        {
            std::unique_lock<std::mutex> lock(m);
            EXPECT_TRUE(wasExecuted.wait_for(
                lock,
                std::chrono::milliseconds(timeoutMilliseconds),
                [this, NumberOfWorkItems]()
                {
                    return count == NumberOfWorkItems;
                }));

            ASSERT_EQ(count, NumberOfWorkItems);
        }
    };
};

TEST_F(AGeoServer_ScaleTests, HandlesLargeNumbersOfUsers)
{
    auto listener = std::static_pointer_cast<GeoServerScaleListener>(trackingListener);
    server.startThreads(2);

    const unsigned int lots{500000};
    addUsersAt(lots, Location{aUserLocation.go(TenMeters, West)});

    std::async([this, &listener]()
               { server.usersInBox(aUser, Width, Height, listener); })
        .get();

    listener->waitForCountAndFailOnTimeout(lots);
}
