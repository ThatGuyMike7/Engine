#ifndef ENGINE_CORE_WINDOW_INCLUDED
#define ENGINE_CORE_WINDOW_INCLUDED

#include <Engine/Core/Event.hpp>
#include <Engine/Core/Input/Keyboard.hpp>
#include <optional>
#include <functional>
#include <vector>
#include <cstdint>

namespace Engine::Core
{
    /**
     * Alias for `SDL_GLContext`.
     */
    using GLContext = void*;

    /**
     * Alias for `SDL_GL_GetProcAddress` and `GLADloadproc`.
     */
    using GLProcAddress_t = void* (char const*);

    /**
     * `SDL_Window*` for the current SDL2 window abstraction.
     * Could be for example `HWND` when writing a WinAPI window abstraction.
     */
    using WindowHandle = void*;

    /**
     * Client area size.
     */
    struct WindowSize
    {
        int width;
        int height;
    };

    /**
     * Non-copyable, non-move-assignable.
     * Encapsulates a window and GL context.
     * The window is initially hidden, call `Show` to make it visible.
     * Only one instance of this class may exist.
     * Must only be used on the main thread.
     */
    class Window
    {
    public:
        /**
         * Client area size.
         */
        struct SizeChangedEventData
        {
            int32_t width;
            int32_t height;
        };

        Event<SizeChangedEventData>& OnSizeChangedEvent();

    private:
        EventOwner<SizeChangedEventData> onSizeChangedOwner;

    public:
        /**
         * Open a window and create a GL context.
         * May throw if something went wrong.
         */
        explicit Window(char const *title = "Game", int width = 800, int height = 600);
        ~Window();
        Window(Window const&) = delete;
        Window& operator=(Window const&) = delete;
        Window(Window &&other);
        Window& operator=(Window &&other) = delete;

        [[nodiscard]] GLProcAddress_t* GetGLProcAddress() const;

        [[nodiscard]] Input::Keyboard const& Keyboard() const;

        void PollEvents();

        void Swap() const;

        void Show() const;
        void Hide() const;

        [[nodiscard]] bool ShouldQuit() const;

        /**
         * Info useful for calling 'glViewport'.
         * More efficient than calling `Width()` and `Height()` individually.
         * \returns Client area width.
         */
        [[nodiscard]] WindowSize Size() const;

        /**
         * Info useful for calling `glViewport`.
         * \returns Client area width.
         */
        [[nodiscard]] int Width() const;

        /**
         * Info useful for calling `glViewport`.
         * \returns Client area width.
         */
        [[nodiscard]] int Height() const;

        [[nodiscard]] WindowHandle Handle();

    private:
        inline static bool isCreated = false;

        /**
         * Must be called before anything else SDL related.
         * May throw if something went wrong.
         */
        void InitSDL();

        /**
         * Request a specific OpenGL profile.
         * Must be called before creating SDL window to have an effect.
         * May throw if something went wrong.
         */
        void ConfigureGLProfile() const;

        /**
         * Create a new GL context for the window and make it current.
         * Must be called after the SDL window has been created.
         * May throw if something went wrong.
         */
        void CreateGLContext();

        /**
         * Open an OpenGL window.
         * May throw if something went wrong.
         */
        void CreateWindow(char const *title, int width, int height);
        void CloseWindow();

        GLContext GLContext;
        WindowHandle windowHandle;
        bool isSDLInitialized;
        bool shouldQuit;
        Input::Keyboard keyboard;
    };
}

#endif