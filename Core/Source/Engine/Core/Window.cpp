#include <Engine/Core/Window.hpp>
#include <Engine/Core/String.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <stdexcept>

namespace Engine::Core
{
    Window::Window(char const *title, int width, int height)
        : GLContext(nullptr), windowHandle(nullptr), isSDLInitialized(false), shouldQuit(false)
    {
        if (isCreated)
        {
            throw std::runtime_error(
                    "Something went wrong constructing window: A window already exists."
            );
        }

        InitSDL();
        ConfigureGLProfile();
        CreateWindow(title, width, height);
        CreateGLContext();

        isCreated = true;
    }

    Window::~Window()
    {
        if (GLContext != nullptr)
        {
            SDL_GL_DeleteContext(GLContext);
        }
        if (windowHandle != nullptr)
        {
            CloseWindow();
        }
        if (isSDLInitialized)
        {
            SDL_Quit();
            isCreated = false;
        }
    }

    Window::Window(Window &&other)
        : GLContext(other.GLContext), windowHandle(other.windowHandle),
        isSDLInitialized(other.isSDLInitialized), shouldQuit(other.shouldQuit)
    {
        other.GLContext = nullptr;
        other.windowHandle = nullptr;
        other.isSDLInitialized = false;
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
                    shouldQuit = true;
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
        auto SDLWindow = static_cast<SDL_Window*>(windowHandle);
        SDL_GL_SwapWindow(SDLWindow);
    }

    bool Window::ShouldQuit() const
    {
        return shouldQuit;
    }

    WindowSize Window::Size() const
    {
        auto SDLWindow = static_cast<SDL_Window*>(windowHandle);
        WindowSize size;
        SDL_GL_GetDrawableSize(SDLWindow, &size.width, &size.height);
        return size;
    }

    int Window::Width() const
    {
        auto SDLWindow = static_cast<SDL_Window*>(windowHandle);
        int width;
        SDL_GL_GetDrawableSize(SDLWindow, &width, nullptr);
        return width;
    }

    int Window::Height() const
    {
        auto SDLWindow = static_cast<SDL_Window*>(windowHandle);
        int height;
        SDL_GL_GetDrawableSize(SDLWindow, nullptr, &height);
        return height;
    }

    [[nodiscard]] WindowHandle Window::Handle()
    {
        return windowHandle;
    }

    void Window::InitSDL()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw std::runtime_error(
                    BuildString("Something went wrong initializing SDL: ", SDL_GetError())
            );
        }
        isSDLInitialized = true;
    }

    void Window::ConfigureGLProfile() const
    {
        if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) != 0)
        {
            auto message =
                    BuildString("Something went wrong "
                                "setting attribute \"SDL_GL_CONTEXT_PROFILE_MASK\": ",
                                SDL_GetError()
                    );
            throw std::runtime_error(message);
        }
        if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4) != 0)
        {
            auto message =
                    BuildString("Something went wrong "
                                "setting attribute \"SDL_GL_CONTEXT_MAJOR_VERSION\": ",
                                SDL_GetError()
                    );
            throw std::runtime_error(message);
        }
        if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6) != 0)
        {
            auto message =
                    BuildString("Something went wrong "
                                "setting attribute \"SDL_GL_CONTEXT_MINOR_VERSION\": ",
                                SDL_GetError()
                    );
            throw std::runtime_error(message);
        }

        // Verify that we got what we asked for.
        int profileMask;
        int majorVersion;
        int minorVersion;
        if (SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profileMask) != 0)
        {
            auto message =
                    BuildString("Something went wrong "
                                "getting attribute \"SDL_GL_CONTEXT_PROFILE_MASK\": ",
                                SDL_GetError()
                    );
            throw std::runtime_error(message);
        }
        if (SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &majorVersion) != 0)
        {
            auto message =
                    BuildString("Something went wrong "
                                "getting attribute \"SDL_GL_CONTEXT_MAJOR_VERSION\": ",
                                SDL_GetError()
                    );
            throw std::runtime_error(message);
        }
        if (SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minorVersion) != 0)
        {
            auto message =
                    BuildString("Something went wrong "
                                "getting attribute \"SDL_GL_CONTEXT_MINOR_VERSION\": ",
                                SDL_GetError()
                    );
            throw std::runtime_error(message);
        }
        if (profileMask != SDL_GL_CONTEXT_PROFILE_CORE ||
            majorVersion != 4 ||
            minorVersion != 6)
        {
            throw std::runtime_error("OpenGL 4.6 Core is not available.");
        }
    }

    void Window::CreateGLContext()
    {
        auto SDLWindow = static_cast<SDL_Window*>(windowHandle);
        GLContext = SDL_GL_CreateContext(SDLWindow);
        if (GLContext == nullptr)
        {
            throw std::runtime_error(
                    BuildString("Something went wrong creating GL context: ", SDL_GetError())
            );
        }
    }

    void Window::CreateWindow(char const *title, int width, int height)
    {
        Uint32 flags = SDL_WINDOW_OPENGL;
        SDL_Window *SDLWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if (SDLWindow == nullptr)
        {
            auto message =
                    BuildString("Something went wrong creating window: ", SDL_GetError());
            throw std::runtime_error(message);
        }
        windowHandle = SDLWindow;
    }

    void Window::CloseWindow()
    {
        auto SDLWindow = static_cast<SDL_Window*>(windowHandle);
        SDL_DestroyWindow(SDLWindow);
        windowHandle = nullptr;
    }
}