#ifndef ENGINE_CORE_SYSTEM_INCLUDED
#define ENGINE_CORE_SYSTEM_INCLUDED

#include <Engine/Core/Window.hpp>
#include <new>
#include <cstdint>
#include <optional>

namespace Engine::Core
{
    constexpr size_t CacheLineSize = std::hardware_destructive_interference_size;

    struct SystemInfo
    {
        uint32_t pageSize;
    };
    SystemInfo GetSystemInfo();

    /** Show an error message box,
      * or print the message to `stderr` if no message box could be shown.
      * Must only be called on the main thread.
      */
    void ShowErrorMessageBox(char const *message,
                             std::optional<Window> parentWindow = std::nullopt);
}

#endif