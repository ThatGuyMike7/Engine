#include <Engine/Graphics/Graphics.hpp>

#include <glad/glad.h>
#include <iostream>

namespace Engine::Graphics
{
    bool LoadGL(Engine::Core::GLProcAddress_t *GLProcAddress)
    {
        if (!gladLoadGLLoader(static_cast<GLADloadproc>(GLProcAddress)))
        {
            std::cout << "Something went wrong loading GL proc address." << std::endl;
            return false;
        }
        return true;
    }

    int GLMajorVersion()
    {
        return GLVersion.major;
    }

    int GLMinorVersion()
    {
        return GLVersion.minor;
    }
}