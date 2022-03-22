#include <Engine/Core/Memory/GeneralPurposeAllocator.hpp>
#include <Engine/Core/Common.hpp>
#include <cstdlib>

#if defined(ENGINE_WINDOWS)
#include <malloc.h>
#endif

namespace Engine::Core::Memory
{
    void* GeneralPurposeAllocator::Allocate(size_t size)
    {
        return std::malloc(size);
    }

    void* GeneralPurposeAllocator::AllocateAligned(size_t size, size_t alignment)
    {
        #if defined(ENGINE_WINDOWS)
        return _aligned_malloc(size, alignment);
        #else
        // "The size parameter must be an integral multiple of alignment."
        // Also we know that `alignment` is a power of 2.
        return std::aligned_alloc(alignment, RoundUpToNextPowerOfTwo(size, alignment));
        #endif
    }

    void GeneralPurposeAllocator::Free(void *ptr)
    {
        std::free(ptr);
    }

    void GeneralPurposeAllocator::FreeAligned(void *ptr)
    {
        #if defined(ENGINE_WINDOWS)
        _aligned_free(ptr);
        #else
        std::free(ptr);
        #endif
    }
}