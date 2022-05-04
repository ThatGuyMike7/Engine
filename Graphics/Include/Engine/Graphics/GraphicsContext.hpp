#ifndef ENGINE_GRAPHICS_GRAPHICS_CONTEXT_INCLUDED
#define ENGINE_GRAPHICS_GRAPHICS_CONTEXT_INCLUDED

#include <Engine/Core/Window.hpp>
#include <optional>

namespace Engine::Graphics
{
    void Clear(float r, float g, float b);

    [[nodiscard]] int GLMajorVersion();
    [[nodiscard]] int GLMinorVersion();

    // Non-copyable, non-moveable.
    // Encapsulates a window, GL context, and GL function pointers.
    // Only one instance of this class may exist.
    // Must be used on the thread it was created on.
    class GraphicsContext
    {
    public:
        // Open a window, create GL context and make it current, and load GL function pointers.
        // May throw if something went wrong.
        explicit GraphicsContext(char const *title = "Game", int width = 800, int height = 600);
        ~GraphicsContext();
        GraphicsContext(GraphicsContext const&) = delete;
        GraphicsContext& operator=(GraphicsContext const&) = delete;
        GraphicsContext(GraphicsContext &&other) = delete;
        GraphicsContext& operator=(GraphicsContext &&other) = delete;

        Engine::Core::Window& Window();

        // TODO: Call when window client area resizes.
        void Resize() const;

    private:
        inline static bool isCreated = false;

        // Load GL function pointers.
        // Must be called before calling any OpenGL functions.
        // May throw if something went wrong.
        void LoadGLFunctions() const;

        Engine::Core::Window window;
    };
}

#endif