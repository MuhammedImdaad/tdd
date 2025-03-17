#include <gtest/gtest.h>

class Soundex
{
private:
    auto zeroPad(const std::string&input) const
    {
        return input + "000";
    }
public:
    auto encode(const std::string &input) const
    {
        return zeroPad(input);
    }
};

TEST(SoundexEncoding, RetainsSoleLetterOfOneLetterWord)
{
    Soundex soundex;
    auto encoded = soundex.encode("A");
    ASSERT_EQ(encoded, "A000");
}

TEST(SoundexEncoding, PadsWithZerosToEnsureThreeDigits)
{
    Soundex soundex;
    auto encoded = soundex.encode("|");
    ASSERT_STREQ(encoded.c_str(), "|000");
}