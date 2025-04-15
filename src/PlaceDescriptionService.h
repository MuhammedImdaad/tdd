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
        const std::string &longitude) const
    {
        std::string server{"http://open.mapquestapi.com/"};

        std::string document{"nominatim/v1/reverse"};

        return server + document + "?" +

               keyValue("format", "json") + "&" +

               keyValue("lat", latitude) + "&" +

               keyValue("lon", longitude);
    }

    std::string summaryDescription(
        const std::string &response) const
    {
        AddressExtractor extractor;
        auto address = extractor.addressFrom(response);
        return address.road + ", " + address.city + ", " +
               address.state + ", " + address.country;
    }

    // primary method to be tested
    std::string summaryDescription(
        const std::string &latitude,
        const std::string &longitude) const
    {
        auto request = createGetRequestUrl(latitude, longitude);
        auto response = http->get(request);
        return response.empty() ? "" : summaryDescription(response);
    }
};