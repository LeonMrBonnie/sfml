#pragma once

#include <string>
#include <vector>

#include "./memory.hpp"
#include "./helpers.hpp"

namespace sfml
{
    class Pattern
    {
        std::vector<uint8_t> bytes;

    public:
        Pattern(const std::string& signature)
        {
            char c;
            for(uint64_t i = 0; i < signature.size(); i++)
            {
                c = signature[i];
                if(c == ' ') continue;
                bool isLast = i == (signature.size() - 1);
                if(c != '?' && !isLast)
                {
                    auto first  = CharToHex(c);
                    auto second = CharToHex(c + 1);
                    if(first != INVALID_BYTE && second != INVALID_BYTE) bytes.push_back(static_cast<uint8_t>((first * 0x10) + second));
                }
                else
                {
                    bytes.push_back(INVALID_BYTE);
                }
            }
        }

        auto GetBytes()
        {
            return bytes;
        }
    };
}  // namespace sfml
