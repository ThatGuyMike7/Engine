#ifndef ENGINE_CORE_COMMON_INCLUDED
#define ENGINE_CORE_COMMON_INCLUDED

#include <cassert>
#include <cstdint>

#if defined(ENGINE_DEBUG) && !defined(ENGINE_ASSERT) && !defined(ENGINE_ASSERT_MSG)
#define ENGINE_ASSERT(exp) assert(exp)
#define ENGINE_ASSERT_MSG(exp, msg) assert((msg, exp))
#endif

namespace Engine::Core
{
    // \returns Offset from `ptr` where `alignment` is satisfied.
    size_t AlignAddress(void *ptr, size_t alignment);

    constexpr bool IsPowerOfTwo(size_t n)
    {
        return (n != 0) && !(n & (n - 1));
    }

    constexpr size_t RoundUpToNext(size_t n, size_t multiple)
    {
        ENGINE_ASSERT(multiple != 0);
        return ((n + multiple - 1) / multiple) * multiple;
    }

    // Faster than `RoundUpToNext`.
    // \param multiple Must be a power of 2.
    constexpr size_t RoundUpToNextPowerOfTwo(size_t n, size_t multiple)
    {
        ENGINE_ASSERT(IsPowerOfTwo(multiple));
        return (n + multiple - 1) & -multiple;
    }
}

#endif