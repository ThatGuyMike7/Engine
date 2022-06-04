#include <Engine/Core/Window.hpp>
#include <Engine/Core/String.hpp>
#include <Engine/Core/Common.hpp>
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

    Event<Window::SizeChangedEventData>& Window::OnSizeChangedEvent()
    {
        return onSizeChangedOwner.GetEvent();
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
            {
                break;
            }
            case SDL_WINDOWEVENT:
            {
                switch (event.window.event)
                {
                default:
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    shouldQuit = true;
                    break;
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    auto data = SizeChangedEventData{ event.window.data1, event.window.data2 };
                    onSizeChangedOwner.Fire(data);
                    break;
                }
                break;
            }
            case SDL_KEYDOWN:
            {
                Input::ScanCode key = static_cast<Input::ScanCode>(event.key.keysym.scancode);
                keyboard.PressKey(key);
                break;
            }
            case SDL_KEYUP:
            {
                Input::ScanCode key = static_cast<Input::ScanCode>(event.key.keysym.scancode);
                keyboard.ReleaseKey(key);
                break;
            }
            }
        }
    }

    void Window::Swap() const
    {
        auto sdlWindow = static_cast<SDL_Window*>(windowHandle);
        SDL_GL_SwapWindow(sdlWindow);
    }

    void Window::Show() const
    {
        auto sdlWindow = static_cast<SDL_Window*>(windowHandle);
        SDL_ShowWindow(sdlWindow);
    }

    void Window::Hide() const
    {
        auto sdlWindow = static_cast<SDL_Window*>(windowHandle);
        SDL_HideWindow(sdlWindow);
    }

    bool Window::ShouldQuit() const
    {
        return shouldQuit;
    }

    WindowSize Window::Size() const
    {
        auto sdlWindow = static_cast<SDL_Window*>(windowHandle);
        WindowSize size;
        SDL_GL_GetDrawableSize(sdlWindow, &size.width, &size.height);
        return size;
    }

    int Window::Width() const
    {
        auto sdlWindow = static_cast<SDL_Window*>(windowHandle);
        int width;
        SDL_GL_GetDrawableSize(sdlWindow, &width, nullptr);
        return width;
    }

    int Window::Height() const
    {
        auto sdlWindow = static_cast<SDL_Window*>(windowHandle);
        int height;
        SDL_GL_GetDrawableSize(sdlWindow, nullptr, &height);
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
        auto sdlWindow = static_cast<SDL_Window*>(windowHandle);
        GLContext = SDL_GL_CreateContext(sdlWindow);
        if (GLContext == nullptr)
        {
            throw std::runtime_error(
                    BuildString("Something went wrong creating GL context: ", SDL_GetError())
            );
        }
    }

    void Window::CreateWindow(char const *title, int width, int height)
    {
        Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE;
        SDL_Window *sdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if (sdlWindow == nullptr)
        {
            auto message =
                    BuildString("Something went wrong creating window: ", SDL_GetError());
            throw std::runtime_error(message);
        }
        windowHandle = sdlWindow;
    }

    void Window::CloseWindow()
    {
        auto sdlWindow = static_cast<SDL_Window*>(windowHandle);
        SDL_DestroyWindow(sdlWindow);
        windowHandle = nullptr;
    }
}