#include <Engine/Core/Window.hpp>
#include <Engine/Graphics/GraphicsContext.hpp>
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

    Int foo = { 0 };
    list.Insert(list.Count(), foo);
    for (size_t i = 0; i < list.Count(); i++)
    {
        std::cout << list[i].value;
    }
    std::cout << std::endl;

    list.Insert(3, std::move(foo));
    for (size_t i = 0; i < list.Count(); i++)
    {
        std::cout << list[i].value;
    }
    std::cout << std::endl;

    list.PopBack();
    list.PopBack();
    for (size_t i = 0; i < list.Count(); i++)
    {
        std::cout << list[i].value;
    }
    std::cout << std::endl;

    std::cout << "Capacity before shrink to fit: " << list.Capacity() << std::endl;
    list.ShrinkToFit();
    std::cout << "Capacity after shrink to fit: " << list.Capacity() << std::endl;
    std::cout << "Clearing list..." << std::endl;
    std::cout << "Elements: ";
    list.Clear();
    for (size_t i = 0; i < list.Count(); i++)
    {
        std::cout << list[i].value;
    }
    std::cout << std::endl;
    ///////

    Engine::Graphics::GraphicsContext context;
    std::cout << "OpenGL " << Engine::Graphics::GLMajorVersion() << "." << Engine::Graphics::GLMinorVersion() << std::endl;

    while (!context.Window().ShouldQuit())
    {
        context.Window().PollEvents();

        Engine::Graphics::Clear(0.2f, 0.4f, 0.7f);
        context.Window().Swap();
    }

    std::cout << "Done." << std::endl;
    return 0;
}