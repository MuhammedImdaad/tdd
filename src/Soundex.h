#pragma once

class Soundex
{
private:
    static const std::unordered_map<char, char> encodings;

    constexpr static int MaxCodeLength{4};
    constexpr static char noDigit{'#'};

    auto zeroPad(const std::string &input) const
    {
        auto paddingSize = MaxCodeLength - input.size();
        return input + std::string(paddingSize, '0');
    }

    std::string head(const std::string &input) const
    {
        return std::string(1, std::toupper(input.front()));
    }

    char lastDigit(const std::string &word) const
    {
        return word.empty() ? noDigit : std::tolower(word.back());
    }

    void encodeHead(const std::string &input, std::string &encoded) const
    {
        encoded += encodedDigit(input.front());
    }

    bool isVowel(char letter) const
    {
        return std::string("aeiou").find(letter) != std::string::npos;
    }

    void encodeTail(const std::string &input, std::string &encoded) const
    {
        // within input string, upto maxcodelength
        for (std::size_t i = 1; i < input.size() && encoded.size() < MaxCodeLength; i++)
        {
            char digit = encodedDigit(input[i]);
            if (digit != noDigit &&
                (digit != lastDigit(encoded) || isVowel(input[i - 1])))
                encoded += digit;
        }
    }

    std::string encodedDigits(const std::string &input) const
    {
        std::string encoded;
        encodeHead(input, encoded);
        encodeTail(input, encoded);
        return encoded;
    }

public:
    char encodedDigit(char digit) const
    {
        const auto it = encodings.find(std::tolower(digit));
        return it == encodings.end() ? noDigit : it->second;
    }
    
    auto encode(const std::string &input) const
    {
        return zeroPad(head(input) + encodedDigits(input).substr(1));
    }
};

const std::unordered_map<char, char> Soundex::encodings{
    {'b', '1'},
    {'f', '1'},
    {'p', '1'},
    {'v', '1'},
    {'c', '2'},
    {'g', '2'},
    {'j', '2'},
    {'k', '2'},
    {'q', '2'},
    {'s', '2'},
    {'x', '2'},
    {'z', '2'},
    {'d', '3'},
    {'t', '3'},
    {'l', '4'},
    {'m', '5'},
    {'n', '5'},
    {'r', '6'},
};