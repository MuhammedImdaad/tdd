#include <PlaceDescriptionService.h>

// Implementation of PlaceDescriptionService methods (if needed)
// Currently, all methods are implemented inline in the header file.
std::string PlaceDescriptionService::createGetRequestUrl(
    const std::string &latitude,
    const std::string &longitude) const
{
    std::string server{"http://open.mapquestapi.com/"};

    std::string document{"nominatim/v1/reverse"};

    return server + document + "?" +

           keyValue("format", "json") + "&" +

           keyValue("lat", latitude) + "&" +

           keyValue("lon", longitude);
}

std::string PlaceDescriptionService::summaryDescription(
    const std::string &response) const
{
    AddressExtractor extractor;
    auto address = extractor.addressFrom(response);
    return address.road + ", " + address.city + ", " +
           address.state + ", " + address.country;
}

std::string PlaceDescriptionService::summaryDescription(
    const std::string &latitude,
    const std::string &longitude) const
{
    auto request = createGetRequestUrl(latitude, longitude);
    auto response = http->get(request);
    return response.empty() ? "" : summaryDescription(response);
}