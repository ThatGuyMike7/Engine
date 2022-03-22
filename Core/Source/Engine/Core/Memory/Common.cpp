#include <Engine/Core/Common.hpp>

namespace Engine::Core::Memory
{
    size_t AlignAddress(void *ptr, size_t alignment)
    {
        std::uintptr_t intPtr = reinterpret_cast<std::uintptr_t>(ptr);
        return alignment - (intPtr % alignment);
    }
}