#pragma once

#include <stdint.h>

namespace sfml
{
    constexpr uint8_t INVALID_BYTE = UINT8_MAX;

    // Taken from BigBaseV2
    // https://github.com/huds0nx/BigBaseV3/blob/master/BigBaseV3/src/memory/pattern.cpp
    static char CharToUpper(char c)
    {
        return c >= 'a' && c <= 'z' ? static_cast<char>(c + ('A' - 'a')) : static_cast<char>(c);
    }
    static uint8_t CharToHex(char c)
    {
        switch(CharToUpper(c))
        {
            case '0': return static_cast<uint8_t>(0);
            case '1': return static_cast<uint8_t>(1);
            case '2': return static_cast<uint8_t>(2);
            case '3': return static_cast<uint8_t>(3);
            case '4': return static_cast<uint8_t>(4);
            case '5': return static_cast<uint8_t>(5);
            case '6': return static_cast<uint8_t>(6);
            case '7': return static_cast<uint8_t>(7);
            case '8': return static_cast<uint8_t>(8);
            case '9': return static_cast<uint8_t>(9);
            case 'A': return static_cast<uint8_t>(10);
            case 'B': return static_cast<uint8_t>(11);
            case 'C': return static_cast<uint8_t>(12);
            case 'D': return static_cast<uint8_t>(13);
            case 'E': return static_cast<uint8_t>(14);
            case 'F': return static_cast<uint8_t>(15);
            default: return INVALID_BYTE;
        }
    }

    static inline uint64_t GetModuleSize(Memory& mem)
    {
        auto dos = mem.As<IMAGE_DOS_HEADER*>();
        auto nt  = mem.Add(dos->e_lfanew).As<IMAGE_NT_HEADERS*>();
        return nt->OptionalHeader.SizeOfImage;
    }
}  // namespace sfml
