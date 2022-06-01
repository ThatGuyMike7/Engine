#include <Engine/Core/Collections/List.hpp>
#include <iostream>

namespace Engine::Core::Collections
{
    void TestList()
    {
        struct alignas(64) Int
        {
            int value;
        };

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
    }
}