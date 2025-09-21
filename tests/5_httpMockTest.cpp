#include <gmock/gmock.h> // Google Mock framework for mocking dependencies
#include <Http.h> // Interface for HTTP operations
#include <PlaceDescriptionService.h> // Service to format place descriptions

using ::testing::_;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;


// Mock class for Http INTERFACE using Google Mock
class HttpMock : public Http
{
public:
    // Mock initialize method
    MOCK_METHOD(void, initialize, (), (override));
    // Mock get method to simulate HTTP GET requests
    MOCK_METHOD(std::string, get, (const std::string &url), (override, const));
};

// [----------] 4 tests from APlaceDescriptionService
// Test fixture for PlaceDescriptionService tests
class APlaceDescriptionService : public testing::Test
{
public:
    // Example valid coordinates for testing
    std::string ValidLatitude = "39.7392";
    std::string ValidLongitude = "-104.9903";
};


// Test that Http::initialize is called before Http::get
TEST_F(APlaceDescriptionService, HttpInitializeBeforeGet)
{
    HttpMock http;

    InSequence forceExpectationOrder; // Enforce call order for expectations
    EXPECT_CALL(http, initialize);    // Expect initialize to be called first
    EXPECT_CALL(http, get);           // Then expect get to be called

    PlaceDescriptionService service(&http);
    // Call summaryDescription, which should trigger the expected sequence
    service.summaryDescription(ValidLatitude, ValidLongitude);
}


// Test that PlaceDescriptionService makes the correct HTTP request to obtain address
TEST_F(APlaceDescriptionService, MakesHttpRequestToObtainAddress)
{
    NiceMock<HttpMock> http; // NiceMock allows unexpected calls without failing

    PlaceDescriptionService service(&http);
    std::string urlStart{"http://open.mapquestapi.com/nominatim/v1/reverse?format=json&"};
    std::string expected{urlStart + "lat=" + ValidLatitude + "&" + "lon=" + ValidLongitude};

    EXPECT_CALL(http, get(expected)); // Expect the correct URL to be requested

    service.summaryDescription(ValidLatitude, ValidLongitude);
}


// Test that PlaceDescriptionService formats the retrieved address into a summary string
TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription)
{
    NiceMock<HttpMock> http;
    PlaceDescriptionService service(&http);

    // Simulate a single call to get() returning a specific JSON address
    EXPECT_CALL(http, get(_)).WillOnce(Return(
        R"({
        "address" : {
            "road" : "Drury Ln",
            "city" : "Fountain",
            "state" : "CO",
            "country" : "US"
        }
    })"));

    // The service should parse the JSON and format the address correctly
    auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
    ASSERT_EQ(description, "Drury Ln, Fountain, CO, US");
}