#pragma once
#include <Location.h>

class Area
{
public:
    Area(const Location &location, double width, double height)
    {
        left_ = location.go(width / 2, West).longitude();
        right_ = location.go(width / 2, East).longitude();
        top_ = location.go(height / 2, North).latitude();
        bottom_ = location.go(height / 2, South).latitude();
    };
    Location upperLeft() const
    {
        return Location{top_, left_};
    };
    Location upperRight() const
    {
        return Location{top_, right_};
    };
    Location lowerRight() const
    {
        return Location{bottom_, right_};
    };
    Location lowerLeft() const
    {
        return Location{bottom_, left_};
    };
    bool inBounds(const Location &location) const
    {
        return location.latitude() <= top_ &&
               location.latitude() >= bottom_ &&
               location.longitude() <= right_ &&
               location.longitude() >= left_;
    };

private:
    double left_;
    double right_;
    double top_;
    double bottom_;
};