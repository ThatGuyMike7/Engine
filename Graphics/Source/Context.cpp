#include <Engine/Graphics/Context.hpp>
#include <glad/glad.h>
#include <iostream>

namespace Engine::Graphics
{
    void Clear(float r, float g, float b)
    {
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    int GLMajorVersion()
    {
        return GLVersion.major;
    }

    int GLMinorVersion()
    {
        return GLVersion.minor;
    }

    Context::Context(Engine::Core::Context const &core)
        : core(&core)
    {
    }

    Context::~Context()
    {
        contextCreated = false;
    }

    Context::Context(Context &&other)
        : core(other.core)
    {
        other.core = nullptr;
    }

    Context& Context::operator=(Context &&other)
    {
        if (&other != this)
        {
            core = other.core;
            other.core = nullptr;
        }
        return *this;
    }

    std::optional<Context> Context::Create(Engine::Core::Context const &core)
    {
        if (contextCreated)
        {
            std::cout << "Error: There must only be 1 Graphics Context." << std::endl;
            return std::nullopt;
        }
        Context context(core);

        // NOTE: I assume glad doesn't have to be unloaded somehow
        //       in case the graphics context is destroyed and a new one is constructed.
        if (!gladLoadGLLoader(static_cast<GLADloadproc>(core.GetGLProcAddress())))
        {
            std::cout << "Something went wrong setting GL proc address loader." << std::endl;
            return std::nullopt;
        }

        context.Resize();

        Context::contextCreated = true;
        return std::optional<Context>(std::move(context));
    }

    void Context::Resize() const
    {
        glViewport(0, 0, core->Width(), core->Height());
    }
}