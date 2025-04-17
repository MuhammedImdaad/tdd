#include <gtest/gtest.h>
#include <Http.h>
#include <PlaceDescriptionService.h>

class APlaceDescriptionService : public testing::Test
{
public:
    std::string ValidLatitude = "39.7392";
    std::string ValidLongitude = "-104.9903";
};

// HttpStub is the type of our test double
class HttpStub : public Http
{
public:
    virtual void initialize() override {};

    // a test double that returns a hard-coded value is a​ stub​.
    // You can similarly refer to the ​get ​method as a​ stub method​.
    std::string get(const std::string &url) const override
    {
        verify(url);
        return returnResponse;
    }

    void verify(const std::string &url) const
    {
        ASSERT_EQ(url, expectedURL);
    }

    std::string returnResponse;
    std::string expectedURL;
};

/*
    Test-driving the Place Description Service presents a challenge—
    the dependency on the REST call is problematic for at least a few reasons.
    Making an actual HTTP call to invoke a REST service is very slow and will bog down your test run.
    The service might not always be available.
    You can’t guarantee what results the call will return.

    HTTP giving you trouble? Create a test double HTTP implementation!
*/
TEST_F(APlaceDescriptionService, ReturnsDescriptionForValidLocation)
{
    HttpStub stub; // test double to avoid http service dependency
    std::string urlStart{"http://open.mapquestapi.com/nominatim/v1/reverse?format=json&"};
    std::string expected{urlStart + "lat=" + APlaceDescriptionService::ValidLatitude + "&" + "lon=" + APlaceDescriptionService::ValidLongitude};
    stub.expectedURL = expected;
    stub.returnResponse = R"({
        "address" : {
            "road" : "Drury Ln",
            "city" : "Fountain",
            "state" : "CO",
            "country" : "US"
        }
    })";

    // PlaceDescriptionService object knows not whether it holds a production Http instance or an instance designed solely for testing
    PlaceDescriptionService service{&stub};
    auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
    ASSERT_EQ(description, "Drury Ln, Fountain, CO, US");
}