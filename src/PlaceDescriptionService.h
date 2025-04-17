#pragma once

#include <Http.h>
#include <Address.h>

class PlaceDescriptionService
{
    Http *http;

public:
    PlaceDescriptionService(Http *http)
        : http(http)
    {
        http->initialize();
    }

    std::string keyValue(
        const std::string &key,
        const std::string &value) const
    {
        return key + "=" + value;
    }

    std::string createGetRequestUrl(
        const std::string &latitude,
        const std::string &longitude) const;

    std::string summaryDescription(
        const std::string &response) const;

    // primary method to be tested
    std::string summaryDescription(
        const std::string &latitude,
        const std::string &longitude) const;
};