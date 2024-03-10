#pragma once

#include <format>
#include <stdexcept>

namespace Engine
{
    class OpenGlException final : public std::runtime_error
    {
    public:
        OpenGlException(int error, const char* description)
            : std::runtime_error(std::format("OpenGL error {}: {}", error, description)) {}
    };
}
