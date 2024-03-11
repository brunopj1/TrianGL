#pragma once

#include <exception>
#include <format>
#include <stdexcept>
#include <string>

namespace Engine
{
    class FileNotFoundException final : public std::runtime_error
    {
    public:
        FileNotFoundException(const std::string& filePath)
            : std::runtime_error(std::format("The file '{}' was not found", filePath))
        {}
    };
}
