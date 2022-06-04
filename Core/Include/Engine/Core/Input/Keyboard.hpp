#ifndef ENGINE_CORE_KEYBOARD_INCLUDED
#define ENGINE_CORE_KEYBOARD_INCLUDED

#include <Engine/Core/Input/ScanCode.hpp>
#include <cstdint>
#include <bitset>

namespace Engine::Core::Input
{
    class Keyboard
    {
    public:
        [[nodiscard]] bool IsKeyDown(ScanCode key) const;

        void PressKey(ScanCode key);
        void ReleaseKey(ScanCode key);

    private:
        std::bitset<NumScanCodes> keyboardState;
    };
}

#endif
