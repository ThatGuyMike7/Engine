#ifndef ENGINE_CORE_WINDOW_INCLUDED
#define ENGINE_CORE_WINDOW_INCLUDED

#include <optional>

namespace Engine::Core
{
    // Alias for `SDL_GLContext`.
    using GLContext = void*;

    // Alias for `SDL_GL_GetProcAddress` and `GLADloadproc`.
    using GLProcAddress_t = void* (char const*);

    // `SDL_Window*` for the current SDL2 window abstraction.
    // Could be for example `HWND` when writing a WinAPI window abstraction.
    using WindowHandle = void*;

    // Non-copyable, non-moveable.
    // Encapsulates a window and GL context.
    // Only one instance of this class may exist.
    // Must be used on the thread it was created on.
    class Window
    {
    public:
        // Open a window and create a GL context.
        // May throw if something went wrong.
        explicit Window(char const *title = "Game", int width = 800, int height = 600);
        ~Window();
        Window(Window const&) = delete;
        Window& operator=(Window const&) = delete;
        Window(Window &&other) = delete;
        Window& operator=(Window &&other) = delete;

        [[nodiscard]] GLProcAddress_t* GetGLProcAddress() const;

        void PollEvents();

        void Swap() const;

        [[nodiscard]] bool ShouldQuit() const;

        // Info useful for calling `glViewport`.
        // \returns Client area width.
        [[nodiscard]] int Width() const;

        // Info useful for calling `glViewport`.
        // \returns Client area height.
        [[nodiscard]] int Height() const;

    private:
        inline static bool isCreated = false;

        // Must be called before anything else SDL related.
        // May throw if something went wrong.
        void InitSDL();

        // Request a specific OpenGL profile.
        // Must be called before creating SDL window to have an effect.
        // May throw if something went wrong.
        void ConfigureGLProfile() const;

        // Create a new GL context for the window and make it current.
        // Must be called after the SDL window has been created.
        // May throw if something went wrong.
        void CreateGLContext();

        // Open an OpenGL window.
        // May throw if something went wrong.
        void CreateWindow(char const *title, int width, int height);
        void CloseWindow();

        GLContext GLContext;
        WindowHandle windowHandle;
        bool isSDLInitialized;
        bool shouldQuit;
    };
}

#endif