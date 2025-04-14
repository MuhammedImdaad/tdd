#pragma once
#include <Location.h>
#include <string>

class User
{
public:
   User(const std::string &name, Location location)
       : name_(name), location_(location) {}

   std::string name() const { return name_; }
   Location location() const { return location_; }

private:
   std::string name_;
   Location location_;
};