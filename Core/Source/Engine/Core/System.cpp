#include <Engine/Core/System.hpp>
#include <SDL2/SDL.h>

#if defined(ENGINE_WINDOWS)
#include <Windows.h>
#endif

#include <iostream>

namespace Engine::Core
{
    SystemInfo GetSystemInfo()
    {
        #if defined(ENGINE_WINDOWS)
        SYSTEM_INFO info;
        GetSystemInfo(&info);

        SystemInfo _info = { info.dwPageSize };
        return _info;
        #endif
    }

    void ShowErrorMessageBox(char const *message, std::optional<Window> parentWindow)
    {
        SDL_Window* sdlWindow = nullptr;
        if (parentWindow)
        {
            sdlWindow = static_cast<SDL_Window*>(parentWindow->Handle());
        }

        int status = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, sdlWindow);
        if (status != 0)
        {
            std::cerr << "Something went wrong showing message box: " << SDL_GetError()
                      << std::endl;
            std::cerr << message << std::endl;
        }
    }
}