#pragma once

namespace sfml
{
    class Memory
    {
        uint8_t* data;

    public:
        Memory(uint8_t* data) : data(data) {}
        explicit Memory(std::nullptr_t data) : data(nullptr) {}
        explicit Memory(void* data) : data(data) {}

        template<class T>
        Memory Add(T offset)
        {
            return Memory(data + offset);
        }

        template<class T>
        Memory Sub(T offset)
        {
            return Memory(data - offset);
        }

        template<class T>
        T As()
        {
            return reinterpret_cast<T>(data);
        }

        inline bool operator==(Memory& other)
        {
            return data == other.data;
        }

        inline operator bool()
        {
            return data != nullptr;
        }

        template<typename Return = void, typename... Args>
        Return Call(Args... args)
        {
            return ((Return(*)(Args...))data)(args...);
        }

        template<typename Type>
        Type Value()
        {
            return (Type)*data;
        }

        template<typename Type>
        void Assign(Type value)
        {
            *data = value;
        }
    };
}  // namespace sfml
