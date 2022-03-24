#ifndef ENGINE_CORE_COLLECTIONS_LIST_INCLUDED
#define ENGINE_CORE_COLLECTIONS_LIST_INCLUDED

#include <Engine/Core/Common.hpp>
#include <Engine/Core/Memory/MemoryCoordinator.hpp>
#include <algorithm>

namespace Engine::Core::Collections
{
    // Contiguous sequence container type.
    // `std::vector` replacement.
    template <typename T>
    class List
    {
    public:
        // \param capacity Initial size of the internal buffer expressed in elements. Must not be 0.
        List(size_t capacity = 8)
            : count(0)
        {
            ENGINE_ASSERT(capacity != 0);

            bufferSize = Spacing * capacity;
            buffer = static_cast<char*>(Memory::MC.AllocateAligned(bufferSize, Alignment));
        }

        ~List()
        {
            char *ptr = buffer;
            for (size_t i = 0; i < count; i++)
            {
                T *element = reinterpret_cast<T*>(ptr);
                element->~T();
                ptr += Spacing;
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
            return bufferSize / Spacing;
        }

        T& Add(T const &value)
        {
            size_t pos = count * Spacing;
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
            size_t pos = count * Spacing;
            if (pos + sizeof(T) > bufferSize)
            {
                GrowBuffer();
            }
            char *ptr = buffer + pos;
            T *element = new(ptr) T(std::move(value)); // Move-construct.
            count++;
            return *element;
        }

        void RemoveAt(size_t index)
        {
            #if defined(ENGINE_DEBUG)
            ENGINE_ASSERT(index < count);
            #endif

            if (index == count - 1) // Last element
            {
                At(index).~T();
                count--;
            }
            else
            {
                T *dest = &At(index);
                //dest->~T();
                std::move(dest + 1, End(), dest);
                count--;
            }
        }

    private:
        static constexpr size_t Alignment = alignof(T);
        static constexpr size_t Spacing = sizeof(T);

        // \returns One past the end.
        T* End()
        {
            char *ptr = buffer + count * Spacing;
            return reinterpret_cast<T*>(ptr);
        }

        T& At(size_t index)
        {
            char *ptr = buffer + index * Spacing;
            return *reinterpret_cast<T*>(ptr);
        }

        void GrowBuffer()
        {
            bufferSize *= 3;
            buffer = static_cast<char*>(Memory::MC.ReallocateAligned(buffer, bufferSize, Alignment));
        }

        char *buffer;
        size_t bufferSize;
        // Element count.
        size_t count;
    };
}

#endif