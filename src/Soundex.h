#pragma once
class Soundex
{
    constexpr static int MaxCodeLength{4};

private:
    auto zeroPad(const std::string &input) const
    {
        auto paddingSize = MaxCodeLength - input.size();
        return input + std::string(paddingSize, '0');
    }

    auto head(const std::string &input) const
    {
        return input.substr(0, 1);
    }

    char lastDigit(const std::string& word) const 
    {
        return word.empty() ? '\0' : word.back();
    }

    std::string encodedDigits(const std::string &input) const
    {
        std::string encoded;

        // within input string, upto maxcodelength
        for (std::size_t i = 1; i < input.size() && encoded.size() < MaxCodeLength - 1; i++)
        {
            if (encodedDigit(input[i]) != lastDigit(encoded))
                encoded += encodedDigit(input[i]);
        }

        return encoded;
    }

public:
    char encodedDigit(char digit) const
    {
        static const std::unordered_map<char, char> encodings{
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

        const auto it = encodings.find(digit);
        return it == encodings.end() ? '\0' : it->second;
    }
    auto encode(const std::string &input) const
    {
        return zeroPad(head(input) + encodedDigits(input));
    }
};