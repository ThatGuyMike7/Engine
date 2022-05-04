#ifndef ENGINE_CORE_STRING_INCLUDED
#define ENGINE_CORE_STRING_INCLUDED

#include <string>

namespace Engine::Core
{
    template <typename... Ts>
    [[nodiscard]] std::string BuildString(Ts&&... args)
    {
        constexpr size_t InitialCapacity = 48;

        std::string str;
        str.reserve(InitialCapacity);

        // Fold expression. Roughly expands to:
        // `(str += std::forward<Ts[0]>(args[0])), (str += std::forward<Ts[1]>(args[1])), ...`
        return ((str += std::forward<Ts>(args)), ...);
    }
}

#endif
