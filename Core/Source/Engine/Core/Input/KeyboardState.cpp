#include <Engine/Core/Input/KeyboardState.hpp>
#include <Engine/Core/Common.hpp>

namespace Engine::Core::Input
{
    bool KeyboardState::operator[](ScanCode scanCode) const
    {
        size_t index = static_cast<size_t>(scanCode);
        return scanCodes[index];
    }
}