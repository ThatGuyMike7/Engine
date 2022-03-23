#if defined(ENGINE_WINDOWS)

#include <Engine/Core/Memory/PlatformPageAllocator.hpp>
#include <Windows.h>

namespace Engine::Core::Memory
{
    void PlatformPageAllocator::AllocatePage()
    {
        //VirtualAlloc()
    }
}

#endif