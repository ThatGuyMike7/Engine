#include <Engine/Core/Context.hpp>
#include <Engine/Graphics/Graphics.hpp>

#include <iostream>

int main()
{
    std::optional<Engine::Core::Context> context = Engine::Core::Context::Create("Engine", 800, 600);
    if (!context)
    {
        return 1;
    }

    if (!Engine::Graphics::LoadGL(context->GetGLProcAddress()))
    {
        return 1;
    }

    std::cout << "OpenGL " << Engine::Graphics::GLMajorVersion() << "." << Engine::Graphics::GLMinorVersion() << std::endl;

    while (!context->DesiresQuit())
    {
        context->PollEvents();
    }

    std::cout << "Done." << std::endl;
    return 0;
}