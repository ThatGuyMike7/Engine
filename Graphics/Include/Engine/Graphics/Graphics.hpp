#ifndef ENGINE_GRAPHICS_GRAPHICS_INCLUDED
#define ENGINE_GRAPHICS_GRAPHICS_INCLUDED

#include <Engine/Core/Context.hpp>

namespace Engine::Graphics
{
    bool LoadGL(Engine::Core::GLProcAddress_t *GLProcAddress);

    [[nodiscard]] int GLMajorVersion();
    [[nodiscard]] int GLMinorVersion();
}

#endif