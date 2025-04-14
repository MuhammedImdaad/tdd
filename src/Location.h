#pragma once
#include <cmath>

constexpr double North{ 0 };
constexpr double West{ 90 };
constexpr double South{ 180 };
constexpr double East{ 270 };

class Location
{
public:
    double m_latitude = 0;
    double m_longitude = 0;

    const double Pi{4.0 * atan(1.0)};
    const double ToRadiansConversionFactor{Pi / 180};
    const double RadiusOfEarthInMeters{6372000};

    Location() {}
    Location(double latitude, double longitude)
        : m_latitude(latitude), m_longitude(longitude)
    {
    }

    double latitude() const { return m_latitude; }
    double longitude() const { return m_longitude; }

    bool isUnknown() const
    {
        return m_latitude == 0 && m_longitude == 0;
    }

    Location go(double meters, double bearing) const;

    double toRadians(double degrees) const
    {
        return degrees * ToRadiansConversionFactor;
    }

    double latitudeAsRadians() const
    {
        return toRadians(m_latitude);
    }

    double longitudeAsRadians() const
    {
        return toRadians(m_longitude);
    }

    double toCoordinate(double radians) const
    {
        return radians * (180 / Pi);
    }
};