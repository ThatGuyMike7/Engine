#include <Engine/Core/System.hpp>

#if defined(ENGINE_WINDOWS)
#include <Windows.h>
#endif

namespace Engine::Core
{
    #if defined(ENGINE_WINDOWS)
    SystemInfo GetSystemInfo()
    {
        SYSTEM_INFO info;
        GetSystemInfo(&info);

        SystemInfo _info;
        _info.pageSize = info.dwPageSize;
        return _info;
    }
    #endif
}