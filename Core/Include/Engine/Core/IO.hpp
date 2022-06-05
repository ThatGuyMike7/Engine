#ifndef ENGINE_CORE_IO_INCLUDED
#define ENGINE_CORE_IO_INCLUDED

#include <optional>
#include <string>
#include <string_view>

namespace Engine::Core
{
    /**
     * \returns File contents on success.
     */
    [[nodiscard]] std::optional<std::string> ReadFile(std::string_view path);
}

#endif
