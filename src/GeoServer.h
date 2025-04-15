#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>

#include <Location.h>
#include <User.h>
#include <Area.h>
#include <ThreadPool.h>

class GeoServerListner;
// The GeoServer provides support for client applications seeking 
// to track the geographic location of large numbers of users 
class GeoServer
{
    std::map<std::string, Location> users;
    std::unique_ptr<ThreadPool> pool;

public:
    void track(const std::string &name);
    bool isTracking(const std::string &name) const;
    void stopTracking(const std::string &name);
    Location locationOf(const std::string &name) const;
    void updateLocation(const std::string &name, const Location &location);

    void usersInBox(
        const std::string &user, double widthInMeters, double heightInMeters, 
        const std::shared_ptr<GeoServerListner>& listner) const;

    bool isDifferentUserInBounds(
        const std::pair<std::string, Location> &each,
        const std::string &user,
        const Area &box) const;

    void useThreadPool(std::unique_ptr<ThreadPool>& pool)
    {
        this->pool = std::move(pool);
    }

    void startThreads(unsigned int numberOfThreads)
    {
        pool->start(numberOfThreads);
    }
};

class GeoServerListner
{
public:
    virtual void updated(const User &user) = 0;
};