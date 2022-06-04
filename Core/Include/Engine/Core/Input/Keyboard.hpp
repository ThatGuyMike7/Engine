#ifndef ENGINE_CORE_KEYBOARD_INCLUDED
#define ENGINE_CORE_KEYBOARD_INCLUDED

#include <Engine/Core/Input/ScanCode.hpp>
#include <cstdint>
#include <bitset>

namespace Engine::Core
{
    class Window;
}

namespace Engine::Core::Input
{
    class Keyboard
    {
        friend class Engine::Core::Window;

    public:
        bool IsKeyDown(ScanCode key) const;

    private:
        std::bitset<NumScanCodes> keyboardState;

        void PressKey(ScanCode key);
        void ReleaseKey(ScanCode key);
    };
}

#endif
