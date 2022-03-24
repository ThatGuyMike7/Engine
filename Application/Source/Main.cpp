#include <Engine/Core/Context.hpp>
#include <Engine/Graphics/Context.hpp>
#include <Engine/Core/Memory/MemoryCoordinator.hpp>
#include <Engine/Core/System.hpp>
#include <Engine/Core/Collections/List.hpp>
#include <iostream>

struct alignas(64) Int
{
    int value;
};

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

    ///////
    Engine::Core::Collections::List<Int> list;
    for (int i = 0; i < 10; i++)
    {
        Int element = { i };
        list.Add(element);
    }

    for (size_t i = 0; i < list.Count(); i++)
    {
        std::cout << list[i].value;
    }
    std::cout << std::endl;

    list.RemoveAt(3);
    for (size_t i = 0; i < list.Count(); i++)
    {
        std::cout << list[i].value;
    }
    std::cout << std::endl;

    list.RemoveAt(list.Count() - 1);
    for (size_t i = 0; i < list.Count(); i++)
    {
        std::cout << list[i].value;
    }
    std::cout << std::endl;
    ///////

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