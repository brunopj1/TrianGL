#pragma once

#include <exception>

namespace Engine::Exceptions::Core
{
    class OpenGlException : public std::exception
    {
    private:
        int m_Error;
        const char* m_Description;

    public:
        OpenGlException(int error, const char* description);
        ~OpenGlException() override = default;

    public:
        [[nodiscard]] const char* what() const override;
    };
}
