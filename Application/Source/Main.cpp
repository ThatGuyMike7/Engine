#include <Engine/Core/Context.hpp>
#include <Engine/Graphics/Context.hpp>
#include <Engine/Core/Memory/MemoryCoordinator.hpp>
#include <iostream>

int main()
{
    int *ptr = static_cast<int*>(Engine::Core::Memory::MC.Allocate(sizeof(int)));
    *ptr = 5;
    std::cout << "*ptr: " << *ptr << std::endl;
    Engine::Core::Memory::MC.Free(ptr);

    #ifdef ENGINE_WINDOWS
    std::cout << "Windows" << std::endl;
    #endif

    #ifdef ENGINE_DEBUG
    std::cout << "Debug" << std::endl;
    #endif

    std::optional<Engine::Core::Context> core = Engine::Core::Context::Create("Engine", 800, 600);
    if (!core)
    {
        return 1;
    }

    std::optional<Engine::Graphics::Context> graphics = Engine::Graphics::Context::Create(core.value());
    if (!graphics)
    {
        return 1;
    }

    std::cout << "OpenGL " << Engine::Graphics::GLMajorVersion() << "." << Engine::Graphics::GLMinorVersion() << std::endl;

    while (!core->DesiresQuit())
    {
        core->PollEvents();

        Engine::Graphics::Clear(0.2f, 0.4f, 0.7f);
        core->Swap();
    }

    std::cout << "Done." << std::endl;
    return 0;
}