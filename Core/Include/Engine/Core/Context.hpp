#ifndef ENGINE_CORE_CONTEXT_INCLUDED
#define ENGINE_CORE_CONTEXT_INCLUDED

#include <optional>

namespace Engine::Core
{
    // `SDL_Window*` for the current SDL2 window abstraction.
    // Could be for example `HWND` when writing a WinAPI window abstraction.
    using WindowHandle = void*;

    // Non-constructible, non-copyable.
    class Context
    {
    public:
        ~Context();
        Context(const Context&) = delete;
        Context& operator=(const Context&) = delete;
        Context(Context &&other);
        Context& operator=(Context &&other);

        [[nodiscard]] static std::optional<Context> Create();

        // Create and open a new window.
        // If a window is already created, close it and create a new window.
        [[nodiscard]] bool CreateWindow(const char *title, int width, int height);
        void CloseWindow();

        void PollEvents();

        [[nodiscard]] bool DesiresQuit() const;

    private:
        Context();

        inline static bool contextCreated = false;
        WindowHandle window;
        bool initialized;
        bool desiresQuit;
    };
}

#endif