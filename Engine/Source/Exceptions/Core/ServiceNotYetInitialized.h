#pragma once

#include <exception>
#include <string>

namespace Engine::Exceptions::Core
{
    class ServiceNotYetInitialized final : public std::exception
    {
    private:
        std::string m_Message;

    public:
        ServiceNotYetInitialized(std::string serviceName);
        ~ServiceNotYetInitialized() override = default;

    public:
        [[nodiscard]] const char* what() const override;
    };
}
