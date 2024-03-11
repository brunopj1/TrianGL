#pragma once

#include <format>
#include <stdexcept>
#include <string>

namespace Engine
{
    class FileTooBigException final : public std::runtime_error
    {
    public:
        FileTooBigException(const std::string& filePath, const std::string& maximumSize)
            : std::runtime_error(std::format("The file '{}' exceeds the maximum size of {}", filePath, maximumSize))
        {}
    };
}
