#include <string>

class converter
{
    static const std::vector<std::pair<int, std::string>> map;
    static constexpr int LIMIT = 3999;

public:
    static std::string convert(unsigned int arabic)
    {
        if (arabic > LIMIT)
            return "";
            
        std::string roman;
        for (auto& item : map)
        {
            while (arabic >= item.first)
            {
                roman += item.second;
                arabic -= item.first;
            }
        }

        return roman;
    }
};

const std::vector<std::pair<int, std::string>> converter::map = {
    {1000, "M"},

    {900, "CM"},
    {500, "D"},
    {400, "CD"},
    {100, "C"},

    {90, "XC"},
    {50, "L"},
    {40, "XL"},
    {10, "X"},
    
    {9, "IX"},
    {5, "V"},
    {4, "IV"},
    {1, "I"},
};