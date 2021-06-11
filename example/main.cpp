#include "../include/sfml.hpp"
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

int main()
{
    // Create the module
    sfml::Module module(GetModuleHandle(nullptr));

    // Search for a pattern
    auto address = module.Scan("AA BB CC ? ? ? ? DDD EE FF GG HH II JJ ? KK LL ? MM NN ?");
    if(!address)
    {
        std::cout << "Failed to find address" << std::endl;
        return -1;
    }

    // Read data at some offset
    auto data = address.Add(4).As<int*>();

    // Call the address as a function
    auto returnData = address.Call<int>("abc", 123, (void*)0);

    // Set the address to some value
    address.Assign<uint32_t>(32);

    // Get the value at the address
    auto val = address.Value<uint32_t>();
}
