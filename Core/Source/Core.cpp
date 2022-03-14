#include <Engine/Core/Core.hpp>

#include <SDL2/SDL.h>
#include <iostream>

namespace Engine::Core
{
    void Hello()
    {
        std::cout << "Hello from Core!" << std::endl;
    }

    void TestSDL()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "Something went wrong initializing SDL: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return;
        }

        SDL_Quit();
    }
}