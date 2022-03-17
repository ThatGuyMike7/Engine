#ifndef ENGINE_CORE_CONTEXT_INCLUDED
#define ENGINE_CORE_CONTEXT_INCLUDED

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
    class Context
    {
    public:
        ~Context();
        Context(Context const&) = delete;
        Context& operator=(Context const&) = delete;
        Context(Context &&other);
        Context& operator=(Context &&other);

        // Open a window and create a GL context.
        [[nodiscard]] static std::optional<Context> Create(char const *windowTitle, int windowWidth, int windowHeight);

        GLProcAddress_t* GetGLProcAddress() const;

        void PollEvents();

        [[nodiscard]] bool DesiresQuit() const;

    private:
        Context();

        [[nodiscard]] bool CreateWindow(char const *title, int width, int height);
        void CloseWindow();

        inline static bool contextCreated = false;
        GLContext GLContext;
        WindowHandle window;
        bool initialized;
        bool desiresQuit;
    };
}

#endif