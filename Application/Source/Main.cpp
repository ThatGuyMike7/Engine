#include <Engine/Core/Window.hpp>
#include <Engine/Graphics/GraphicsContext.hpp>
#include <Engine/Core/Memory/MemoryCoordinator.hpp>
#include <Engine/Core/System.hpp>
#include <Engine/Core/Collections/List.hpp>
#include <iostream>

void OnWindowSizeChanged(Engine::Core::Window::SizeChangedEventData const& data)
{
    std::cout << "Window Client Area Size changed: " << data.width << "x" << data.height << std::endl;
}

int main()
{
    #if defined(ENGINE_WINDOWS)
    std::cout << "Windows" << std::endl;

    auto systemInfo = Engine::Core::GetSystemInfo();
    std::cout << "Page Size: " << systemInfo.pageSize << std::endl;
    #endif

    #if defined(ENGINE_DEBUG)
    std::cout << "Debug" << std::endl;
    #endif

    auto maybeContext = Engine::Graphics::GraphicsContext::Create();
    if (!maybeContext)
    {
        return 0;
    }

    auto context = std::move(*maybeContext);
    context.Window().OnSizeChangedEvent().Subscribe((&OnWindowSizeChanged));

    Engine::Graphics::Clear(0.2f, 0.4f, 0.7f);
    context.Window().Show();

    std::cout << "OpenGL " << Engine::Graphics::GLMajorVersion() << "." << Engine::Graphics::GLMinorVersion() << std::endl;

    while (!context.Window().ShouldQuit())
    {
        context.Window().PollEvents();

        if (context.Window().Keyboard().IsKeyDown(Engine::Core::Input::ScanCode::W))
        {
            std::cout << "W down" << std::endl;
        }
        else
        {
            std::cout << "W up" << std::endl;
        }

        Engine::Graphics::Clear(0.2f, 0.4f, 0.7f);
        context.Window().Swap();
    }

    std::cout << "Done." << std::endl;
    return 0;
}