#include <Engine/Core/Context.hpp>
#include <SDL2/SDL.h>
#include <iostream>

namespace Engine::Core
{
    Context::Context()
        : GLContext(nullptr), window(nullptr), initialized(false), desiresQuit(false)
    {
    }

    Context::~Context()
    {
        if (GLContext != nullptr)
        {
            SDL_GL_DeleteContext(GLContext);
        }
        if (window != nullptr)
        {
            CloseWindow();
        }
        if (initialized)
        {
            SDL_Quit();
        }

        contextCreated = false;
    }

    Context::Context(Context &&other)
        : GLContext(other.GLContext), window(other.window), initialized(other.initialized), desiresQuit(other.desiresQuit)
    {
        other.GLContext = nullptr;
        other.window = nullptr;
        other.initialized = false;
        other.desiresQuit = false;
    }

    Context& Context::operator=(Context &&other)
    {
        if (&other != this)
        {
            GLContext = other.GLContext;
            window = other.window;
            initialized = other.initialized;
            desiresQuit = other.desiresQuit;
            other.GLContext = nullptr;
            other.window = nullptr;
            other.initialized = false;
            other.desiresQuit = false;
        }
        return *this;
    }

    std::optional<Context> Context::Create(char const *windowTitle, int windowWidth, int windowHeight)
    {
        if (contextCreated)
        {
            std::cout << "Error: There must only be 1 Core Context." << std::endl;
            return std::nullopt;
        }
        Context context;

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "Something went wrong initializing SDL: " << SDL_GetError() << std::endl;
            return std::nullopt;
        }
        context.initialized = true;

        if (!context.SetGLAttributes())
        {
            return std::nullopt;
        }

        if (!context.CreateWindow(windowTitle, windowWidth, windowHeight))
        {
            return std::nullopt;
        }

        auto SDLWindow = static_cast<SDL_Window*>(context.window);
        context.GLContext = SDL_GL_CreateContext(SDLWindow);
        if (context.GLContext == nullptr)
        {
            std::cout << "Something went wrong creating GL context: " << SDL_GetError() << std::endl;
            return std::nullopt;
        }

        Context::contextCreated = true;
        return std::optional<Context>(std::move(context));
    }

    GLProcAddress_t* Context::GetGLProcAddress() const
    {
        return SDL_GL_GetProcAddress;
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

    void Context::Swap() const
    {
        auto SDLWindow = static_cast<SDL_Window*>(window);
        SDL_GL_SwapWindow(SDLWindow);
    }

    bool Context::DesiresQuit() const
    {
        return desiresQuit;
    }

    int Context::Width() const
    {
        auto SDLWindow = static_cast<SDL_Window*>(window);
        int width;
        SDL_GL_GetDrawableSize(SDLWindow, &width, nullptr);
        return width;
    }

    int Context::Height() const
    {
        auto SDLWindow = static_cast<SDL_Window*>(window);
        int height;
        SDL_GL_GetDrawableSize(SDLWindow, nullptr, &height);
        return height;
    }

    bool Context::SetGLAttributes() const
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

    bool Context::CreateWindow(char const *title, int width, int height)
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
        auto SDLWindow = static_cast<SDL_Window*>(window);
        SDL_DestroyWindow(SDLWindow);
        this->window = nullptr;
    }
}