#ifndef ENGINE_CORE_MEMORY_IALLOCATOR_INCLUDED
#define ENGINE_CORE_MEMORY_IALLOCATOR_INCLUDED

namespace Engine::Core::Memory
{
    class IAllocator
    {
        friend class MemoryCoordinator;

    protected:
        IAllocator() = default;
        ~IAllocator() = default;
        IAllocator(IAllocator const&) = default;
        IAllocator& operator=(IAllocator const&) = default;
        IAllocator(IAllocator&&) = default;
        IAllocator& operator=(IAllocator&&) = default;

        // Must be matched with a call to `Free`.
        virtual void* Allocate(size_t size) = 0;

        // Must be matched with a call to `FreeAligned`.
        virtual void* AllocateAligned(size_t size, size_t alignment) = 0;

        // Must be matched with a call to `Free`.
        // \param ptr Must have been previously allocated with `Allocate`.
        virtual void* Reallocate(void *ptr, size_t newSize) = 0;

        // Must be matched with a call to `FreeAligned`.
        // \param ptr Must have been previously allocated with `AllocateAligned`.
        // \param alignment Must be the same value as passed to `AllocateAligned`.
        virtual void* ReallocateAligned(void *ptr, size_t newSize, size_t alignment) = 0;
        virtual void Free(void *ptr) = 0;
        virtual void FreeAligned(void *ptr) = 0;
    };
}

#endif