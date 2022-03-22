#ifndef ENGINE_GRAPHICS_CONTEXT_INCLUDED
#define ENGINE_GRAPHICS_GRAPHICS_INCLUDED

#include <Engine/Core/Context.hpp>
#include <optional>

namespace Engine::Graphics
{
    void Clear(float r, float g, float b);

    [[nodiscard]] int GLMajorVersion();
    [[nodiscard]] int GLMinorVersion();

    // Non-constructible, non-copyable.
    // Important: Core context must not be destroyed before graphics context.
    class Context
    {
    public:
        ~Context();
        Context(Context const&) = delete;
        Context& operator=(Context const&) = delete;
        Context(Context &&other);
        Context& operator=(Context &&other);

        // Load GL functions.
        [[nodiscard]] static std::optional<Context> Create(Engine::Core::Context const &core);

        // Call when window client area resizes.
        void Resize() const;

    private:
        inline static bool created = false;
        Context(Engine::Core::Context const &core);

        Engine::Core::Context const *core;
    };
}

#endif