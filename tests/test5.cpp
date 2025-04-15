#include <gtest/gtest.h>
#include <GeoServer.h>
#include <Location.h>

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

    void SetUp() override
    {
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
};

TEST_F(AGeoServer_UsersInBox, AnswersUsersInSpecifiedRange)
{
    server.updateLocation(

        bUser, Location{aUserLocation.go(Width / 2 - TenMeters, East)});

    auto users = server.usersInBox(aUser, Width, Height);

    ASSERT_EQ(std::vector<std::string>{bUser}, UserNames(users));
}

TEST_F(AGeoServer_UsersInBox, AnswersOnlyUsersWithinSpecifiedRange)
{
    server.updateLocation(

        bUser, Location{aUserLocation.go(Width / 2 + TenMeters, East)});

    server.updateLocation(

        cUser, Location{aUserLocation.go(Width / 2 - TenMeters, East)});

    auto users = server.usersInBox(aUser, Width, Height);

    ASSERT_EQ(std::vector<std::string>{cUser}, UserNames(users));
}

TEST_F(AGeoServer_UsersInBox, HandlesLargeNumbersOfUsers)
{
    Location anotherLocation{aUserLocation.go(10, West)};
    const unsigned int lots{500000};

    for (unsigned int i{0}; i < lots; i++)
    {
        std::string user{"user" + std::to_string(i)};
        server.track(user);
        server.updateLocation(user, anotherLocation);
    }

    auto users = server.usersInBox(aUser, Width, Height);
    ASSERT_EQ(lots, users.size());
}