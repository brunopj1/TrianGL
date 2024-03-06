#pragma once

#include <exception>
#include <string>

namespace Engine::Exceptions::Core
{
    class SingletonNotBeingUsedException final : public std::exception
    {
    private:
        std::string m_Message;

    public:
        SingletonNotBeingUsedException(std::string serviceName, std::string objectName);

    public:
        [[nodiscard]] const char* what() const override;
    };
}
