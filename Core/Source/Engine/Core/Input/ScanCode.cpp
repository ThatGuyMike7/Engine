#include <Engine/Core/Input/ScanCode.hpp>
#include <SDL2/SDL_keyboard.h>

namespace Engine::Core::Input
{
    const char* GetScanCodeName(ScanCode scanCode)
    {
        return SDL_GetScancodeName(static_cast<SDL_Scancode>(scanCode));
    }
}