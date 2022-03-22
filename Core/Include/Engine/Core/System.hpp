#ifndef ENGINE_CORE_SYSTEM_INCLUDED
#define ENGINE_CORE_SYSTEM_INCLUDED

#include <new>

namespace Engine::Core
{
    constexpr size_t CacheLineSize = std::hardware_destructive_interference_size;
}

#endif