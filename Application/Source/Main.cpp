#include <Engine/Core/Context.hpp>
#include <Engine/Graphics/Context.hpp>
#include <Engine/Core/Memory/MemoryCoordinator.hpp>
#include <Engine/Core/System.hpp>
#include <Engine/Core/Collections/List.hpp>
#include <iostream>

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

    Engine::Core::Collections::List<int> list;
    std::cout << "Capacity: " << list.Capacity() << std::endl;
    int i = 0;
    int j = 1;
    int k = 2;

    for (int cnt = 0; cnt < 3; cnt++)
    {
        list.Add(i);
        list.Add(std::move(j));
        list.Add(k);
    }

    for (size_t cnt = 0; cnt < list.Count(); cnt++)
    {
        std::cout << list[cnt] << " ";
    }
    std::cout << std::endl;
    std::cout << "Capacity: " << list.Capacity() << std::endl;

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