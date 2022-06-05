#include <Engine/Graphics/Shader.hpp>
#include <Engine/Core/Common.hpp>
#include <glad/glad.h>
#include <stdexcept>

namespace
{
    /**
     * Map `Engine::Graphics::ShaderType` to OpenGL shader type.
     */
    GLenum ShaderTypeToGLShaderType(Engine::Graphics::ShaderType shaderType)
    {
        switch (shaderType)
        {
        default:
            throw std::runtime_error("Used unsupported shader type. This is a bug.");
        case Engine::Graphics::ShaderType::Vertex:
            return GL_VERTEX_SHADER;
        case Engine::Graphics::ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;
        }
    }
}

namespace Engine::Graphics
{
    Shader::Shader(ShaderType shaderType, ShaderHandle shaderHandle)
        : shaderType(shaderType), shaderHandle(shaderHandle), isHandleValid(true)
    {
    }

    Shader::~Shader()
    {
        if (isHandleValid)
        {
            glDeleteShader(shaderHandle);
        }
    }

    Shader::Shader(Shader &&other)
        : shaderType(other.shaderType), shaderHandle(other.shaderHandle),
          isHandleValid(other.isHandleValid)
    {
        other.isHandleValid = false;
    }

    Shader& Shader::operator=(Shader &&other)
    {
        if (isHandleValid)
        {
            glDeleteShader(shaderHandle);
        }

        shaderType = other.shaderType;
        shaderHandle = other.shaderHandle;
        isHandleValid = other.isHandleValid;

        other.isHandleValid = false;

        return *this;
    }

    std::optional<Shader> Shader::Compile(ShaderCompileInfo *outInfo,
                                          ShaderType shaderType,
                                          char const *shaderSource) noexcept
    {
        GLenum GLShaderType = ShaderTypeToGLShaderType(shaderType);

        ShaderHandle shaderHandle = glCreateShader(GLShaderType);
        glShaderSource(shaderHandle, 1, &shaderSource, nullptr);
        glCompileShader(shaderHandle);

        int32_t success;
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);

        char infoLog[512];
        glGetShaderInfoLog(shaderHandle, 512, nullptr, infoLog);

        ShaderCompileInfo info;
        info.infoLog += infoLog;
        *outInfo = info;

        if (success == GL_TRUE)
        {
            return Shader(shaderType, shaderHandle);
        }
        else
        {
            glDeleteShader(shaderHandle);
            return std::nullopt;
        }
    }

    ShaderType Shader::Type() const
    {
        return shaderType;
    }

    ShaderHandle Shader::Handle() const
    {
        ENGINE_ASSERT_MSG(isHandleValid,
                          "Shader handle is invalid. "
                          "You probably tried accessing the handle of a moved shader.");
        return shaderHandle;
    }

    ShaderProgram::ShaderProgram(ShaderProgramHandle shaderProgramHandle)
        : shaderProgramHandle(shaderProgramHandle), isHandleValid(true)
    {
    }

    ShaderProgram::~ShaderProgram()
    {
        if (isHandleValid)
        {
            glDeleteProgram(shaderProgramHandle);
        }
    }

    ShaderProgram::ShaderProgram(ShaderProgram &&other)
        : shaderProgramHandle(other.shaderProgramHandle), isHandleValid(other.isHandleValid)
    {
        other.isHandleValid = false;
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram &&other)
    {
        if (isHandleValid)
        {
            glDeleteProgram(shaderProgramHandle);
        }

        shaderProgramHandle = other.shaderProgramHandle;
        isHandleValid = other.isHandleValid;

        other.isHandleValid = false;

        return *this;
    }

    std::optional<ShaderProgram> ShaderProgram::Link(ShaderProgramLinkInfo *outInfo,
                                                     std::span<Shader> shaders) noexcept
    {
        // TODO: Validate that there is at least 1 vertex shader?

        if (shaders.empty())
        {
            *outInfo = {};
            return std::nullopt;
        }

        ShaderProgramHandle shaderProgramHandle = glCreateProgram();
        for (auto &&shader : shaders)
        {
            glAttachShader(shaderProgramHandle, shader.Handle());
        }
        glLinkProgram(shaderProgramHandle);

        int32_t success;
        glGetProgramiv(shaderProgramHandle, GL_LINK_STATUS, &success);

        char infoLog[512];
        glGetProgramInfoLog(shaderProgramHandle, 512, nullptr, infoLog);

        ShaderProgramLinkInfo info;
        info.infoLog += infoLog;
        *outInfo = info;

        if(success == GL_TRUE)
        {
            return ShaderProgram(shaderProgramHandle);
        }
        else
        {
            glDeleteProgram(shaderProgramHandle);
            return std::nullopt;
        }
    }

    ShaderProgramHandle ShaderProgram::Handle() const
    {
        ENGINE_ASSERT_MSG(isHandleValid,
                          "Shader program handle is invalid. "
                          "You probably tried accessing the handle of a moved shader program.");
        return shaderProgramHandle;
    }
}









