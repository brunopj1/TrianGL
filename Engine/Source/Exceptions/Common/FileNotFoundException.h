#pragma once

#include <exception>
#include <string>

namespace Engine::Exceptions::Common
{
    class FileNotFoundException final : public std::exception
    {
    private:
        std::string m_FilePath;
        std::string m_Message;

    public:
        FileNotFoundException(std::string filePath);

    public:
        [[nodiscard]] const char* what() const override;
    };
}
