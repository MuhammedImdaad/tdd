#include <GeoServer.h>

void GeoServer::track(const std::string &name)
{
    users.insert({name, Location()});
}

bool GeoServer::isTracking(const std::string &name) const
{
    return users.count(name);
}

void GeoServer::stopTracking(const std::string &name)
{
    if (isTracking(name))
        users.erase(name);
}

void GeoServer::updateLocation(const std::string &name, const Location &location)
{
    if (isTracking(name))
    {
        users[name].m_latitude = location.latitude();
        users[name].m_longitude = location.longitude();
    }
}

Location GeoServer::locationOf(const std::string &name) const
{
    if (isTracking(name))
        return users.at(name);
    return Location{};
}

void GeoServer::usersInBox(
    const std::string &user, double widthInMeters, double heightInMeters,
    GeoServerListner &listner) const
{
    auto location = locationOf(user);
    Area box{location, widthInMeters, heightInMeters};

    // std::vector<User> tracked;
    for (auto &each : users)
        if (isDifferentUserInBounds(each, user, box))
        {
            // tracked.push_back(User{each.first, each.second});
            listner.updated({each.first, each.second});
        }
    // return tracked;
}

bool GeoServer::isDifferentUserInBounds(
    const std::pair<std::string, Location> &each,
    const std::string &user,
    const Area &box) const
{
    if (each.first == user)
        return false;
    return box.inBounds(each.second);
}