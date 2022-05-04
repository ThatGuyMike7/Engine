#include <Engine/Core/Context.hpp>
#include <SDL2/SDL.h>
#include <iostream>

namespace Engine::Core
{
    Window::Window()
        : GLContext(nullptr), handle(nullptr), initialized(false), desiresQuit(false)
    {
    }

    Window::~Window()
    {
        if (GLContext != nullptr)
        {
            SDL_GL_DeleteContext(GLContext);
        }
        if (handle != nullptr)
        {
            CloseWindow();
        }
        if (initialized)
        {
            SDL_Quit();
        }

        created = false;
    }

    Window::Window(Window &&other)
        : GLContext(other.GLContext), handle(other.handle), initialized(other.initialized), desiresQuit(other.desiresQuit)
    {
        other.GLContext = nullptr;
        other.handle = nullptr;
        other.initialized = false;
        other.desiresQuit = false;
    }

    /*
    Window& Window::operator=(Window &&other)
    {
        if (&other != this)
        {
            GLContext = other.GLContext;
            handle = other.handle;
            initialized = other.initialized;
            desiresQuit = other.desiresQuit;
            other.GLContext = nullptr;
            other.handle = nullptr;
            other.initialized = false;
            other.desiresQuit = false;
        }
        return *this;
    }
    */

    std::optional<Window> Window::Create(char const *title, int width, int height)
    {
        if (created)
        {
            std::cout << "Error: There must only be 1 Window." << std::endl;
            return std::nullopt;
        }
        Window window;

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "Something went wrong initializing SDL: " << SDL_GetError() << std::endl;
            return std::nullopt;
        }
        window.initialized = true;

        if (!window.SetGLAttributes())
        {
            return std::nullopt;
        }

        if (!window.CreateWindow(title, width, height))
        {
            return std::nullopt;
        }

        auto SDLWindow = static_cast<SDL_Window*>(window.handle);
        window.GLContext = SDL_GL_CreateContext(SDLWindow);
        if (window.GLContext == nullptr)
        {
            std::cout << "Something went wrong creating GL context: " << SDL_GetError() << std::endl;
            return std::nullopt;
        }

        Window::created = true;
        return std::optional<Window>(std::move(window));
    }

    GLProcAddress_t* Window::GetGLProcAddress() const
    {
        return SDL_GL_GetProcAddress;
    }

    void Window::PollEvents()
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
            case SDL_KEYUP:
            {
                const char *name = SDL_GetScancodeName(event.key.keysym.scancode);
                std::cout << "Key Up: \"" << name << "\"" << std::endl;
                break;
            }
            case SDL_KEYDOWN:
            {
                const char *name = SDL_GetScancodeName(event.key.keysym.scancode);
                std::cout << "Key Down: \"" << name << "\"" << std::endl;
                break;
            }
            }
        }
    }

    void Window::Swap() const
    {
        auto SDLWindow = static_cast<SDL_Window*>(handle);
        SDL_GL_SwapWindow(SDLWindow);
    }

    bool Window::DesiresQuit() const
    {
        return desiresQuit;
    }

    int Window::Width() const
    {
        auto SDLWindow = static_cast<SDL_Window*>(handle);
        int width;
        SDL_GL_GetDrawableSize(SDLWindow, &width, nullptr);
        return width;
    }

    int Window::Height() const
    {
        auto SDLWindow = static_cast<SDL_Window*>(handle);
        int height;
        SDL_GL_GetDrawableSize(SDLWindow, nullptr, &height);
        return height;
    }

    bool Window::SetGLAttributes() const
    {
        if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) != 0)
        {
            std::cout << "Something went wrong setting attribute \"SDL_GL_CONTEXT_PROFILE_MASK\": " << SDL_GetError() << std::endl;
            return false;
        }
        if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) != 0)
        {
            std::cout << "Something went wrong setting attribute \"SDL_GL_CONTEXT_MAJOR_VERSION\": " << SDL_GetError() << std::endl;
            return false;
        }
        if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6) != 0)
        {
            std::cout << "Something went wrong setting attribute \"SDL_GL_CONTEXT_MINOR_VERSION\": " << SDL_GetError() << std::endl;
            return false;
        }

        // Verify that we got what we asked for.
        int profileMask;
        int majorVersion;
        int minorVersion;
        if (SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profileMask) != 0)
        {
            std::cout << "Something went wrong getting attribute \"SDL_GL_CONTEXT_PROFILE_MASK\": " << SDL_GetError() << std::endl;
            return false;
        }
        if (SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &majorVersion) != 0)
        {
            std::cout << "Something went wrong getting attribute \"SDL_GL_CONTEXT_MAJOR_VERSION\": " << SDL_GetError() << std::endl;
            return false;
        }
        if (SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minorVersion) != 0)
        {
            std::cout << "Something went wrong getting attribute \"SDL_GL_CONTEXT_MINOR_VERSION\": " << SDL_GetError() << std::endl;
            return false;
        }
        if (profileMask != SDL_GL_CONTEXT_PROFILE_CORE ||
            majorVersion != 4 ||
            minorVersion != 6)
        {
            std::cout << "OpenGL 4.6 Core is not available." << std::endl;
            return false;
        }

        return true;
    }

    bool Window::CreateWindow(char const *title, int width, int height)
    {
        Uint32 flags = SDL_WINDOW_OPENGL;
        SDL_Window *SDLWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if (SDLWindow == nullptr)
        {
            std::cout << "Something went wrong creating window: " << SDL_GetError() << std::endl;
            return false;
        }
        handle = SDLWindow;
        return true;
    }

    void Window::CloseWindow()
    {
        auto SDLWindow = static_cast<SDL_Window*>(handle);
        SDL_DestroyWindow(SDLWindow);
        handle = nullptr;
    }
}