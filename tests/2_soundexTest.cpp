#include <gtest/gtest.h>
#include <Soundex.h>

/*
 @brief A test fixture class for Soundex encoding tests.
 Google Mock instantiates the fixture class ​once per test​.
 a class that provides support for cross-test reuse.
 */
class SoundexEncoding : public testing::Test
{
public:
    Soundex soundex;
};

// [----------] 12 tests from SoundexEncoding

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) // test case name followed by test within the test case
{
    ASSERT_EQ(soundex.encode("A"), "A000");
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits)
{
    ASSERT_EQ(soundex.encode("|"), "|000");
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
{
    ASSERT_EQ(soundex.encode("Ax"), "A200");
}

TEST_F(SoundexEncoding, IgnoresNonAlphabetics)
{
    ASSERT_EQ(soundex.encode("A#"), "A000");
}

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits)
{
    ASSERT_EQ(soundex.encode("Acdl"), "A234");
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters)
{
    ASSERT_EQ(soundex.encode("Dcdlb").size(), 4);
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLetters)
{
    ASSERT_EQ(soundex.encode("BaAeEiIoOuUhHyYcdl"), "B234");
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings)
{
    ASSERT_EQ(soundex.encodedDigit('b'), soundex.encodedDigit('f'));
    ASSERT_EQ(soundex.encodedDigit('c'), soundex.encodedDigit('g'));
    ASSERT_EQ(soundex.encodedDigit('d'), soundex.encodedDigit('t'));
    ASSERT_EQ(soundex.encode("Abfcgdt"), "A123");
}

TEST_F(SoundexEncoding, UppercasesFirstLetter)
{
    ASSERT_EQ(soundex.encode("abcd").front(), 'A');
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants)
{
    ASSERT_EQ(soundex.encode("BCDL"), soundex.encode("bcdl"));
}

TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st)
{
    ASSERT_EQ(soundex.encode("Bbcd"), "B230");
}

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeparatedByVowels)
{
    ASSERT_EQ(soundex.encode("Jbob"), "J110");
}