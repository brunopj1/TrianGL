#pragma once

#include <exception>
#include <string>

namespace Engine::Exceptions::Core
{
    class FailedToInitializeEngineException final : public std::exception
    {
    private:
        std::string m_Message;

    public:
        FailedToInitializeEngineException(std::string message);
        ~FailedToInitializeEngineException() override = default;

    public:
        [[nodiscard]] const char* what() const override;
    };
}
