#pragma once

class Soundex
{
    constexpr static int MaxCodeLength{4};

private:
    auto zeroPad(const std::string &input) const
    {
        auto paddingSize = MaxCodeLength - input.size();
        return input + std::string(paddingSize, '0');
    }

    auto head(const std::string &input) const
    {
        return input.substr(0, 1);
    }

    auto encodedDigits(const std::string &input) const
    {
        return (input.size() > 1) ? "1" : "";
    }

public:
    auto encode(const std::string &input) const
    {
        return zeroPad(head(input) + encodedDigits(input));
    }
};