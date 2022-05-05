#include <Engine/Graphics/GraphicsContext.hpp>
#include <Engine/Core/System.hpp>
#include <glad/glad.h>
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

    GraphicsContext::GraphicsContext(GraphicsContext &&other)
        : window(std::move(other.window))
    { }

    std::optional<GraphicsContext> GraphicsContext::Create(char const *title,
                                                           int width, int height) noexcept
    {
        try
        {
            return GraphicsContext(title, width, height);
        }
        catch (std::exception const& e)
        {
            Engine::Core::ShowErrorMessageBox(e.what());
            return std::nullopt;
        }
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