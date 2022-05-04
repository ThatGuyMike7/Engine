#include <Engine/Graphics/GraphicsContext.hpp>
#include <glad/glad.h>
#include <iostream>
#include <stdexcept>

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

    GraphicsContext::GraphicsContext(char const *title, int width, int height)
        : window(title, width, height)
    {
        if (isCreated)
        {
            throw std::runtime_error(
                    "Something went wrong constructing graphics context: "
                    "There must only be 1 graphics context."
            );
        }

        LoadGLFunctions();
        Resize();

        isCreated = true;
    }

    GraphicsContext::~GraphicsContext()
    {
        isCreated = false;
    }

    Engine::Core::Window& GraphicsContext::Window()
    {
        return window;
    }

    void GraphicsContext::Resize() const
    {
        glViewport(0, 0, window.Width(), window.Height());
    }

    void GraphicsContext::LoadGLFunctions() const
    {
        if (!gladLoadGLLoader(static_cast<GLADloadproc>(window.GetGLProcAddress())))
        {
            throw std::runtime_error(
                    "Something went wrong setting GL procedure address loader."
            );
        }
    }
}