#pragma once

#include <exception>
#include <string>

namespace Engine::Exceptions::Common
{
    class FileTooBigException final : public std::exception
    {
    private:
        std::string m_FilePath;
        std::string m_Message;

    public:
        FileTooBigException(std::string filePath, std::string maximumSize);

    public:
        [[nodiscard]] const char* what() const override;
    };
}
