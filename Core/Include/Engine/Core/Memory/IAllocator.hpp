#ifndef ENGINE_CORE_MEMORY_IALLOCATOR_INCLUDED
#define ENGINE_CORE_MEMORY_IALLOCATOR_INCLUDED

namespace Engine::Core::Memory
{
    class IAllocator
    {
        friend class MemoryCoordinator;

    protected:
        // Must be matched with a call to `Free`.
        virtual void* Allocate(size_t size) = 0;
        // Must be matched with a call to `FreeAligned`.
        virtual void* AllocateAligned(size_t size, size_t alignment) = 0;
        virtual void Free(void *ptr) = 0;
        virtual void FreeAligned(void *ptr) = 0;
    };
}

#endif