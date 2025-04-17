#include <gmock/gmock.h>
#include <Http.h>
#include <PlaceDescriptionService.h>

using ::testing::_;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;

class HttpMock : public Http
{
public:
    MOCK_METHOD(void, initialize, (), (override));
    MOCK_METHOD(std::string, get, (const std::string &url), (override, const));
};

class APlaceDescriptionService : public testing::Test
{
public:
    std::string ValidLatitude = "39.7392";
    std::string ValidLongitude = "-104.9903";
};

/**********************************************************************************************/
TEST_F(APlaceDescriptionService, HttpInitializeBeforeGet)
{
    HttpMock http;

    InSequence forceExpectationOrder;
    EXPECT_CALL(http, initialize);
    EXPECT_CALL(http, get);

    PlaceDescriptionService service(&http);
    service.summaryDescription(ValidLatitude, ValidLongitude);
}

TEST_F(APlaceDescriptionService, MakesHttpRequestToObtainAddress)
{
    NiceMock<HttpMock> http;

    PlaceDescriptionService service(&http);
    std::string urlStart{"http://open.mapquestapi.com/nominatim/v1/reverse?format=json&"};
    std::string expected{urlStart + "lat=" + ValidLatitude + "&" + "lon=" + ValidLongitude};

    EXPECT_CALL(http, get(expected));

    service.summaryDescription(ValidLatitude, ValidLongitude);
}

TEST_F(APlaceDescriptionService, FormatsRetrievedAddressIntoSummaryDescription)
{
    NiceMock<HttpMock> http;
    PlaceDescriptionService service(&http);

    // a call on the HttpStub object to ​get​() ​will once​ (and only once) ​
    // return​ a specific JSON string value.
    EXPECT_CALL(http, get(_)).WillOnce(Return(
        R"({
        "address" : {
            "road" : "Drury Ln",
            "city" : "Fountain",
            "state" : "CO",
            "country" : "US"
        }
    })"));

    auto description = service.summaryDescription(ValidLatitude, ValidLongitude);
    ASSERT_EQ(description, "Drury Ln, Fountain, CO, US");
}