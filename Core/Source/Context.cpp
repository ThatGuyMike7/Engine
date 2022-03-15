#include <Engine/Core/Context.hpp>

#include <SDL2/SDL.h>
#include <iostream>

namespace Engine::Core
{
    Context::Context()
        : window(nullptr), initialized(false), desiresQuit(false)
    {
    }

    Context::~Context()
    {
        if (window != nullptr)
        {
            CloseWindow();
        }

        if (initialized)
        {
            SDL_Quit();
            contextCreated = false;
        }
    }

    Context::Context(Context &&other)
        : window(other.window), initialized(other.initialized), desiresQuit(other.desiresQuit)
    {
        other.window = nullptr;
        other.initialized = false;
        other.desiresQuit = false;
    }

    Context& Context::operator=(Context &&other)
    {
        window = other.window;
        initialized = other.initialized;
        desiresQuit = other.desiresQuit;
        other.window = nullptr;
        other.initialized = false;
        other.desiresQuit = false;
        return *this;
    }

    std::optional<Context> Context::Create()
    {
        if (contextCreated)
        {
            std::cout << "Error: There must only be 1 Core Context." << std::endl;
            return std::nullopt;
        }

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "Something went wrong initializing SDL: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return std::nullopt;
        }

        Context core;
        core.initialized = true;
        core.contextCreated = true;
        return std::optional<Context>(std::move(core));
    }

    bool Context::CreateWindow(const char *title, int width, int height)
    {
        Uint32 flags = SDL_WINDOW_OPENGL;
        SDL_Window *SDLWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if (SDLWindow == nullptr)
        {
            std::cout << "Something went wrong creating window: " << SDL_GetError() << std::endl;
            return false;
        }
        this->window = SDLWindow;
        return true;
    }

    void Context::CloseWindow()
    {
        auto* SDLWindow = static_cast<SDL_Window*>(window);
        SDL_DestroyWindow(SDLWindow);
        this->window = nullptr;
    }

    void Context::PollEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            default:
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                default:
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    desiresQuit = true;
                    break;
                }
                break;
            }
        }
    }

    bool Context::DesiresQuit() const
    {
        return desiresQuit;
    }
}