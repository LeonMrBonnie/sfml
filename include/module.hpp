#pragma once

#ifdef _WIN32
    #include <Windows.h>
#endif
#include <string>
#include "./memory.hpp"
#include "./pattern.hpp"
#include "./helpers.hpp"

namespace sfml
{
    class Module
    {
        Memory   base;
        uint64_t size;

    public:
        Module(uintptr_t base, uint64_t size = 0) : base((uint8_t*)base), size(size) {}
#ifdef _WIN32
        explicit Module(HMODULE module) : base((uint8_t*)module)
        {
            size = GetModuleSize(base);
        }
        explicit Module(const char* moduleName) : base((uint8_t*)GetModuleHandleA(moduleName))
        {
            size = GetModuleSize(base);
        }
#endif

        uint64_t GetSize()
        {
            return size;
        }

        Memory Start()
        {
            return base;
        }
        Memory End()
        {
            return base.Add(size);
        }

        Memory Scan(const std::string& patternStr)
        {
            return Scan(Pattern(patternStr));
        }
        Memory Scan(Pattern& pattern)
        {
            auto bytes = pattern.GetBytes();
            auto data  = bytes.data();
            auto size  = bytes.size();
            for(uint64_t i = 0; i < size; i++)
            {
                if(PatternMatches(base.Add(i).As<uint8_t*>(), data, size)) return base.Add(i);
            }
            return nullptr;
        }

        static bool PatternMatches(uint8_t* data, uint8_t* signature, uint64_t size)
        {
            for(uint64_t i = 0; i < size; i++)
            {
                if(signature[i] == INVALID_BYTE) continue;
                if(signature[i] == data[i]) continue;
                return false;
            }
            return true;
        }
    };
}  // namespace sfml
