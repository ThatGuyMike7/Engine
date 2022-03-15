#include <Engine/Core/Context.hpp>
#include <Engine/Graphics/Graphics.hpp>

#include <iostream>

int main()
{
    std::optional<Engine::Core::Context> context = Engine::Core::Context::Create();
    if (!context)
    {
        return 0;
    }

    if (!context->CreateWindow("Engine", 800, 600))
    {
        return 0;
    }

    while (!context->DesiresQuit())
    {
        context->PollEvents();
    }

    std::cout << "Done." << std::endl;
    return 0;
}