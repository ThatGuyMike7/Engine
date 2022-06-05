#ifndef ENGINE_GRAPHICS_SHADER_INCLUDED
#define ENGINE_GRAPHICS_SHADER_INCLUDED

#include <optional>
#include <cstdint>
#include <string>
#include <span>

namespace Engine::Graphics
{
    using ShaderHandle = uint32_t;
    using ShaderProgramHandle = uint32_t;

    enum class ShaderType : uint8_t
    {
        Vertex,
        Fragment
    };

    /**
     * Non-constructable, non-copyable.
     * Encapsulates an OpenGL (vertex, fragment, ...) shader.
     * Destructing a shader does not prevent existing shader programs from working,
     * as OpenGL merely flags the shader for deletion until the shader program is deleted.
     */
    class Shader
    {
    public:
        ~Shader();
        Shader(Shader const&) = delete;
        Shader& operator=(Shader const&) = delete;
        Shader(Shader &&other);
        Shader& operator=(Shader &&other);

        struct ShaderCompileInfo
        {
            std::string infoLog;
        };

        /**
         * Compile a shader from source.
         * \returns Shader on success. An empty value if something went wrong.
         */
        [[nodiscard]] static std::optional<Shader> Compile(ShaderCompileInfo *outInfo,
                                                           ShaderType shaderType,
                                                           char const *shaderSource) noexcept;

        [[nodiscard]] ShaderType Type() const;
        [[nodiscard]] ShaderHandle Handle() const;

    private:
        explicit Shader(ShaderType shaderType, ShaderHandle shaderHandle);

        ShaderType shaderType;
        ShaderHandle shaderHandle;
        bool isHandleValid;
    };

    struct ShaderCompileResult
    {
        std::optional<Shader> shader;
        std::string infoLog;
        bool success;
    };

    /**
     * Non-copyable.
     * Encapsulates a linked OpenGL shader program.
     */
    class ShaderProgram
    {
    public:
        ~ShaderProgram();
        ShaderProgram(ShaderProgram const&) = delete;
        ShaderProgram& operator=(ShaderProgram const&) = delete;
        ShaderProgram(ShaderProgram &&other);
        ShaderProgram& operator=(ShaderProgram &&other);

        struct ShaderProgramLinkInfo
        {
            std::string infoLog;
        };

        /**
         * Link one or more shaders into a shader program.
         * \returns Shader program on success. An empty value if something went wrong.
         */
       [[nodiscard]] static std::optional<ShaderProgram> Link(ShaderProgramLinkInfo *outInfo,
                                                              std::span<Shader> shaders) noexcept;

       [[nodiscard]] ShaderProgramHandle Handle() const;
        
    private:
        explicit ShaderProgram(ShaderProgramHandle shaderProgramHandle);

        ShaderProgramHandle shaderProgramHandle;
        bool isHandleValid;
    };
}

#endif
