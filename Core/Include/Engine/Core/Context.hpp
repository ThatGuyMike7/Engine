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

    // Non-constructible, non-copyable.
    // Represents window and associated GL context.
    class Window
    {
    public:
        ~Window();
        Window(Window const&) = delete;
        Window& operator=(Window const&) = delete;
        Window(Window &&other);
        Window& operator=(Window &&other) = delete;

        // Open a window and create a GL context.
        [[nodiscard]] static std::optional<Window> Create(char const *title, int width, int height);

        GLProcAddress_t* GetGLProcAddress() const;

        void PollEvents();

        void Swap() const;

        [[nodiscard]] bool DesiresQuit() const;

        // Info useful for calling `glViewport`.
        // \returns Client area width.
        [[nodiscard]] int Width() const;

        // Info useful for calling `glViewport`.
        // \returns Client area height.
        [[nodiscard]] int Height() const;

    private:
        inline static bool created = false;
        Window();

        // Call before creating window.
        bool SetGLAttributes() const;

        [[nodiscard]] bool CreateWindow(char const *title, int width, int height);
        void CloseWindow();

        GLContext GLContext;
        WindowHandle handle;
        bool initialized;
        bool desiresQuit;
    };
}

#endif