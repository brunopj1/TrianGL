#pragma once

#include <format>
#include <stdexcept>

namespace TGL
{
    class OpenGlException final : public std::runtime_error
    {
    public:
        OpenGlException(i32 error, const char* description)
            : std::runtime_error(std::format("OpenGL error {}: {}", error, description)) {}
    };
}
