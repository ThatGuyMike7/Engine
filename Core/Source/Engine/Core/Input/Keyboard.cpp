#include <Engine/Core/Input/Keyboard.hpp>

namespace Engine::Core::Input
{
    bool Keyboard::IsKeyDown(ScanCode key) const
    {
        return keyboardState[static_cast<size_t>(key)];
    }

    void Keyboard::PressKey(ScanCode key)
    {
        keyboardState.set(static_cast<size_t>(key), true);
    }

    void Keyboard::ReleaseKey(ScanCode key)
    {
        keyboardState.set(static_cast<size_t>(key), false);
    }
}