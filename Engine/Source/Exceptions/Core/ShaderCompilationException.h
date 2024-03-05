#pragma once

#include <exception>
#include <string>

namespace Engine::Exceptions::Core
{
    class ShaderCompilationException final : public std::exception
    {
    private:
        std::string m_Message;

    public:
        ShaderCompilationException(int shaderType, std::string shaderLog);
        ShaderCompilationException(std::string programLog);
        ~ShaderCompilationException() override = default;

    public:
        [[nodiscard]] const char* what() const override;
    };
}
