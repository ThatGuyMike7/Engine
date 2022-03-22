#include <Engine/Core/Memory/MemoryCoordinator.hpp>
#include <new>

// The versions taking `std::align_val_t` are called if alignment requirement of the type
// exceeds `__STDCPP_DEFAULT_NEW_ALIGNMENT__`.

// The following 4 replacement functions are sufficient to handle all allocations,
// as the standard library non-throwing and array versions call these.
void* operator new(size_t size)
{
    return Engine::Core::Memory::NewHandler(size);
    //return Engine::Core::Memory::NewHandler(size, __STDCPP_DEFAULT_NEW_ALIGNMENT__);
}

void* operator new(size_t size, std::align_val_t al)
{
    return Engine::Core::Memory::NewAlignedHandler(size, static_cast<size_t>(al));
}

void operator delete(void* ptr) noexcept
{
    return Engine::Core::Memory::DeleteHandler(ptr);
}

void operator delete(void* ptr, std::align_val_t al) noexcept
{
    return Engine::Core::Memory::DeleteAlignedHandler(ptr);
}