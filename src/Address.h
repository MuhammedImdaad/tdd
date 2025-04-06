#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct Address {
    std::string road;
    std::string city;
    std::string state;
    std::string country;
};

class AddressExtractor {
public:
    Address addressFrom(const std::string& jsonResponse) {
        auto j = json::parse(jsonResponse);
        auto addr = j["address"];

        Address address;
        address.road = addr.value("road", "");
        address.city = addr.value("city", "");
        address.state = addr.value("state", "");
        address.country = addr.value("country", "");
        return address;
    }
};
