// Memory allocation system inspired by GDC talk
// "Beyond the Remake of 'Shadow of the Colossus': A Technical Perspective".
// Link: https://youtu.be/fcBZEZWGYek?t=1711

#ifndef ENGINE_CORE_MEMORY_MEMORY_COORDINATOR_INCLUDED
#define ENGINE_CORE_MEMORY_MEMORY_COORDINATOR_INCLUDED

#include <Engine/Core/Memory/GeneralPurposeAllocator.hpp>

namespace Engine::Core::Memory
{
    void* NewHandler(size_t size);
    void* NewAlignedHandler(size_t size, size_t alignment);
    void DeleteHandler(void *ptr);
    void DeleteAlignedHandler(void *ptr);

    // Non-copyable, non-moveable.
    class MemoryCoordinator
    {
    public:
        MemoryCoordinator();
        ~MemoryCoordinator();
        MemoryCoordinator(MemoryCoordinator const&) = delete;
        MemoryCoordinator& operator=(MemoryCoordinator const&) = delete;
        MemoryCoordinator(MemoryCoordinator&&) = delete;
        MemoryCoordinator& operator=(MemoryCoordinator&&) = delete;

        void* Allocate(size_t size);
        void* AllocateAligned(size_t size, size_t alignment);
        void* Reallocate(void *ptr, size_t newSize);
        void* ReallocateAligned(void *ptr, size_t newSize, size_t alignment);
        void Free(void *ptr);
        void FreeAligned(void *ptr);

    private:
        inline static bool created = false;

        GeneralPurposeAllocator generalPurposeAllocator;
    };

    // Global memory coordinator.
    // All allocations shall go through this object.
    inline MemoryCoordinator MC;
}

#endif