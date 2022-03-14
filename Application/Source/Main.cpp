#include <iostream>
#include <Engine/Core/Core.hpp>
#include <Engine/Graphics/Graphics.hpp>

int main()
{
    std::cout << "Hello from Application!" << std::endl;
    Engine::Core::Hello();
    Engine::Graphics::Hello();
    Engine::Core::TestSDL();
    std::cout << "Done." << std::endl;
    return 0;
}