#pragma once

#include <exception>
#include <string>

namespace Engine::Exceptions::Core
{
    class OpenGlException final : public std::exception
    {
    private:
        std::string m_Message;

    public:
        OpenGlException(int error, const char* description);
        ~OpenGlException() override = default;

    public:
        [[nodiscard]] const char* what() const override;
    };
}
