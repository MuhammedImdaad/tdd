#include <Location.h>

Location Location::go(double meters, double bearing) const
{
    bearing = toRadians(bearing);
    double distance{meters / RadiusOfEarthInMeters};
    double newLat{
        asin(sin(latitudeAsRadians()) * cos(distance) +
             cos(latitudeAsRadians()) * sin(distance) * cos(bearing))};

    double newLong = longitudeAsRadians();
    if (cos(latitudeAsRadians()) != 0)
        newLong =
            fmod(longitudeAsRadians() - asin(sin(bearing) * sin(distance) / cos(newLat)) + Pi,
                 2 * Pi) -
            Pi;

    return Location(toCoordinate(newLat), toCoordinate(newLong));
}