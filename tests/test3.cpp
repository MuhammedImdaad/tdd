#include <gtest/gtest.h>
#include <Http.h>
#include <PlaceDescriptionService.h>

class APlaceDescriptionService : public testing::Test
{
    public:
    static std::string ValidLatitude;
    static std::string ValidLongitude; 
};

// Define static members
std::string APlaceDescriptionService::ValidLatitude = "39.7392";
std::string APlaceDescriptionService::ValidLongitude = "-104.9903";

class HttpStub : public Http
{
    virtual void initialize() override {};

    std::string get(const std::string &url) const override
    {
        verify(url);

        return R"({ 
        "address": {
            "road":"Drury Ln",
            "city":"Fountain",
            "state":"CO",
            "country":"US"
            }
        })";
    }

    void verify(const std::string &url) const
    {
        std::string urlStart = "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&";
        std::string expected(urlStart + "lat=" + APlaceDescriptionService::ValidLatitude + "&" + "lon=" + APlaceDescriptionService::ValidLongitude);
        ASSERT_EQ(url, expected);
    }
};

TEST_F(APlaceDescriptionService, ReturnsDescriptionForValidLocation)
{
    HttpStub stub;
    PlaceDescriptionService service{&stub};
    auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
    ASSERT_EQ(description, "Drury Ln, Fountain, CO, US");
}