#ifndef ENGINE_CORE_MEMORY_PLATFORM_PAGE_ALLOCATOR_INCLUDED
#define ENGINE_CORE_MEMORY_PLATFORM_PAGE_ALLOCATOR_INCLUDED

namespace Engine::Core::Memory
{
    class PlatformPageAllocator
    {
    public:
        void AllocatePage();
    };
}

#endif