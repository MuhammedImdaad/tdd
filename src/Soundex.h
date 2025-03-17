#pragma once

class Soundex
{
private:
    auto zeroPad(const std::string &input) const
    {
        return input + "000";
    }

public:
    auto encode(const std::string &input) const
    {
        return zeroPad(input);
    }
};