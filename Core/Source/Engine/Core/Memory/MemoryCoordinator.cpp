#include <Engine/Core/Memory/MemoryCoordinator.hpp>
#include <Engine/Core/Common.hpp>
#include <iostream>
#include <cstdlib>

namespace Engine::Core::Memory
{
    namespace
    {
        // Called when allocation functions of `MemoryCoordinator` fail.
        void OutOfMemoryHandler()
        {
            std::cout << "Fatal Error: Out of Memory." << std::endl;
            std::exit(1);
        }
    }

    void* NewHandler(size_t size)
    {
        return MC.Allocate(size);
    }

    void* NewAlignedHandler(size_t size, size_t alignment)
    {
        return MC.AllocateAligned(size, alignment);
    }

    void DeleteHandler(void *ptr)
    {
        MC.Free(ptr);
    }

    void DeleteAlignedHandler(void *ptr)
    {
        MC.FreeAligned(ptr);
    }

    MemoryCoordinator::MemoryCoordinator()
    {
        if (created)
        {
            std::cout << "Fatal Error: There must only be 1 Memory Coordinator." << std::endl;
            return;
        }
        created = true;
    }

    MemoryCoordinator::~MemoryCoordinator()
    {
        created = false;
    }

    void* MemoryCoordinator::Allocate(size_t size)
    {
        ENGINE_ASSERT(size > 0);
        void *ptr = generalPurposeAllocator.Allocate(size);
        if (ptr == nullptr)
        {
            OutOfMemoryHandler();
        }
        return ptr;
    }

    void* MemoryCoordinator::AllocateAligned(size_t size, size_t alignment)
    {
        ENGINE_ASSERT(size > 0);
        ENGINE_ASSERT(IsPowerOfTwo(alignment));
        void *ptr = generalPurposeAllocator.AllocateAligned(size, alignment);
        if (ptr == nullptr)
        {
            OutOfMemoryHandler();
        }
        return ptr;
    }

    void* MemoryCoordinator::Reallocate(void *ptr, size_t newSize)
    {
        ENGINE_ASSERT(newSize > 0);
        ptr = generalPurposeAllocator.Reallocate(ptr, newSize);
        if (ptr == nullptr)
        {
            OutOfMemoryHandler();
        }
        return ptr;
    }

    void* MemoryCoordinator::ReallocateAligned(void *ptr, size_t newSize, size_t alignment)
    {
        ENGINE_ASSERT(newSize > 0);
        ENGINE_ASSERT(IsPowerOfTwo(alignment));
        ptr = generalPurposeAllocator.ReallocateAligned(ptr, newSize, alignment);
        if (ptr == nullptr)
        {
            OutOfMemoryHandler();
        }
        return ptr;
    }

    void MemoryCoordinator::Free(void *ptr)
    {
        generalPurposeAllocator.Free(ptr);
    }

    void MemoryCoordinator::FreeAligned(void *ptr)
    {
        generalPurposeAllocator.FreeAligned(ptr);
    }
}