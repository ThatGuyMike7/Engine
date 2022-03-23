#ifndef ENGINE_CORE_COLLECTIONS_LIST_INCLUDED
#define ENGINE_CORE_COLLECTIONS_LIST_INCLUDED

#include <Engine/Core/Common.hpp>
#include <Engine/Core/Memory/MemoryCoordinator.hpp>

namespace Engine::Core::Collections
{
    template <typename T>
    class List
    {
    public:
        // \param capacity Initial size of the internal buffer expressed in elements. Must not be 0.
        List(size_t capacity = 8)
            : count(0)
        {
            ENGINE_ASSERT(capacity != 0);

            void *ptr = buffer + sizeof(T);
            spacing = sizeof(T) + AlignAddress(ptr, alignment);

            bufferSize = spacing * capacity;
            buffer = static_cast<char*>(Memory::MC.AllocateAligned(bufferSize, alignment));
        }

        ~List()
        {
            char *ptr = buffer;
            for (size_t i = 0; i < count; i++)
            {
                T *element = reinterpret_cast<T*>(ptr);
                element->~T();
                ptr += spacing;
            }
            Memory::MC.FreeAligned(buffer);
        }

        List(List const &other);
        List& operator=(List const &other);
        List(List &&other);
        List& operator=(List &&other);

        T const& operator[](size_t index) const
        {
            return At(index);
        }

        T& operator[](size_t index)
        {
            return At(index);
        }

        // \returns Number of elements currently contained in the list.
        size_t Count() const
        {
            return count;
        }

        // \returns How many elements can fit into the current internal buffer.
        size_t Capacity() const
        {
            return bufferSize / spacing;
        }

        T& Add(T const &value)
        {
            size_t pos = count * spacing;
            if (pos + sizeof(T) > bufferSize)
            {
                GrowBuffer();
            }
            char *ptr = buffer + pos;
            T *element = new(ptr) T(value); // Copy-construct.
            count++;
            return *element;
        }

        T& Add(T &&value)
        {
            size_t pos = count * spacing;
            if (pos + sizeof(T) > bufferSize)
            {
                GrowBuffer();
            }
            char *ptr = buffer + pos;
            T *element = new(ptr) T(std::move(value)); // Move-construct.
            count++;
            return *element;
        }

    private:
        static constexpr size_t alignment = alignof(T);

        T& At(size_t index)
        {
            char *ptr = buffer + index * spacing;
            return *reinterpret_cast<T*>(ptr);
        }

        void GrowBuffer()
        {
            bufferSize *= 3;
            buffer = static_cast<char*>(Memory::MC.ReallocateAligned(buffer, bufferSize, alignment));
        }

        char *buffer;
        size_t bufferSize;
        // Space between two elements to satisfy size + alignment.
        size_t spacing;
        // Element count.
        size_t count;
    };
}

#endif