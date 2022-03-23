#ifndef ENGINE_CORE_MEMORY_GENERAL_PURPOSE_ALLOCATOR_INCLUDED
#define ENGINE_CORE_MEMORY_GENERAL_PURPOSE_ALLOCATOR_INCLUDED

#include <Engine/Core/Memory/IAllocator.hpp>

namespace Engine::Core::Memory
{
    class GeneralPurposeAllocator final : public IAllocator
    {
        friend class MemoryCoordinator;

    protected:
        void* Allocate(size_t size) override;
        void* AllocateAligned(size_t size, size_t alignment) override;
        void* Reallocate(void *ptr, size_t newSize) override;
        void* ReallocateAligned(void *ptr, size_t newSize, size_t alignment) override;
        void Free(void *ptr) override;
        void FreeAligned(void *ptr) override;
    };
}

#endif