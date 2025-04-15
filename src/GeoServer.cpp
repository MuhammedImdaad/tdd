#include <GeoServer.h>
#include <iostream>

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
    const std::shared_ptr<GeoServerListner> &listner) const
{
    auto location = locationOf(user);
    Area box{location, widthInMeters, heightInMeters};

    for (auto &each : users)
    {
        Work work([=]()
                  {
            if (isDifferentUserInBounds(each, user, box))
            {
                listner->updated({each.first, each.second});
            } });
        pool->add(work);
    }
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