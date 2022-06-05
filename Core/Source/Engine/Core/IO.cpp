#include <Engine/Core/IO.hpp>
#include <cstdio>

namespace Engine::Core
{
    std::optional<std::string> ReadFile(std::string_view path)
    {
        constexpr size_t InitialSize = 1024;
        constexpr size_t GrowthFactor = 3;

        std::string contents;
        contents.resize(InitialSize);

        std::FILE *stream = std::fopen(path.data(), "rb");
        if (stream == nullptr)
        {
            return std::nullopt;
        }

        // Disable internal stream buffering.
        std::setvbuf(stream, nullptr, _IONBF, 0);

        size_t cursor = 0;
        while (true)
        {
            size_t spaceLeft = contents.size() - cursor;
            size_t numRead = std::fread(contents.data() + cursor, 1, spaceLeft, stream);
            cursor += numRead;
            if (numRead < spaceLeft) // EOF or error.
            {
                break;
            }
            else
            {
                contents.resize(contents.size() * GrowthFactor);
            }
        }

        if (std::feof(stream))
        {
            contents.resize(cursor);
            contents.shrink_to_fit();
            std::fclose(stream);
            return contents;
        }

        if (std::ferror(stream))
        {
            std::fclose(stream);
            return std::nullopt;
        }

        // EOF was not reached.
        std::fclose(stream);
        return std::nullopt;
    }
}