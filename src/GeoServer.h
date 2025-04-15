#pragma once

#include <string>
#include <map>
#include <vector>

#include <Location.h>
#include <User.h>
#include <Area.h>

class GeoServer
{
    std::map<std::string, Location> users;

public:
    void track(const std::string &name);
    bool isTracking(const std::string &name) const;
    void stopTracking(const std::string &name);
    Location locationOf(const std::string &name) const;
    void updateLocation(const std::string &name, const Location &location);

    std::vector<User> usersInBox(
        const std::string &user, double widthInMeters, double heightInMeters) const;

    bool isDifferentUserInBounds(
        const std::pair<std::string, Location> &each,
        const std::string &user,
        const Area &box) const;
};

class GeoServerListner
{
public:
    virtual void updated(const User &user) = 0;
};