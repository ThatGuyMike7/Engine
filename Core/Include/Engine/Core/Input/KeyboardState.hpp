#ifndef ENGINE_CORE_INPUT_KEYBOARD_STATE_INCLUDED
#define ENGINE_CORE_INPUT_KEYBOARD_STATE_INCLUDED

#include <Engine/Core/Input/ScanCode.hpp>
#include <array>

namespace Engine::Core::Input
{
    class KeyboardState
    {
    public:
        [[nodiscard]] bool operator[](ScanCode scanCode) const;

    private:
        std::array<bool, NumScanCodes> scanCodes = {};
    };
}

#endif