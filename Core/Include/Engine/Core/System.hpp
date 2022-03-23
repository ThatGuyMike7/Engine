#ifndef ENGINE_CORE_SYSTEM_INCLUDED
#define ENGINE_CORE_SYSTEM_INCLUDED

#include <new>
#include <cstdint>

namespace Engine::Core
{
    constexpr size_t CacheLineSize = std::hardware_destructive_interference_size;

    struct SystemInfo
    {
        uint32_t pageSize;
    };

    SystemInfo GetSystemInfo();
}

#endif