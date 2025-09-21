#include <gtest/gtest.h>
#include <numberConverter.h>

// [----------] 7 tests from romanConverter
TEST(romanConverter, canConvertOneDigit)
{
    EXPECT_EQ(converter::convert(1), "I");
    EXPECT_EQ(converter::convert(5), "V");
}

TEST(romanConverter, canConvertSingleDigits)
{
    EXPECT_EQ(converter::convert(2), "II");
    EXPECT_EQ(converter::convert(8), "VIII");
}

TEST(romanConverter, specialTreatmentforFourandNine)
{
    EXPECT_EQ(converter::convert(4), "IV");
    EXPECT_EQ(converter::convert(9), "IX");
}

TEST(romanConverter, canConvertTwoDigits)
{
    EXPECT_EQ(converter::convert(10), "X");
    EXPECT_EQ(converter::convert(13), "XIII");
    EXPECT_EQ(converter::convert(19), "XIX");
    EXPECT_EQ(converter::convert(50), "L");
    EXPECT_EQ(converter::convert(80), "LXXX");
    EXPECT_EQ(converter::convert(99), "XCIX");
}

TEST(romanConverter, canConvertThreeDigits)
{
    EXPECT_EQ(converter::convert(101), "CI");
    EXPECT_EQ(converter::convert(134), "CXXXIV");
    EXPECT_EQ(converter::convert(190), "CXC");
    EXPECT_EQ(converter::convert(500), "D");
    EXPECT_EQ(converter::convert(809), "DCCCIX");
    EXPECT_EQ(converter::convert(999), "CMXCIX");
}

TEST(romanConverter, canConvertFourDigits)
{
    EXPECT_EQ(converter::convert(1000), "M");
    EXPECT_EQ(converter::convert(3500), "MMMD");
    EXPECT_EQ(converter::convert(3999), "MMMCMXCIX");
}

TEST(romanConverter, outOfRange)
{
    EXPECT_EQ(converter::convert(0), "");
    EXPECT_EQ(converter::convert(-1), "");
    EXPECT_EQ(converter::convert(4000), "");
    EXPECT_EQ(converter::convert(std::numeric_limits<unsigned int>::max()), "");
    EXPECT_EQ(converter::convert(std::numeric_limits<unsigned int>::min()), "");
    EXPECT_EQ(converter::convert(std::numeric_limits<int>::max()), "");
    EXPECT_EQ(converter::convert(std::numeric_limits<int>::min()), "");
}