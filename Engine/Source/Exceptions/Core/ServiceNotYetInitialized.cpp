#include "ServiceNotYetInitialized.h"

#include "glad/glad.h"
#include <format>

using namespace Engine::Exceptions::Core;

ServiceNotYetInitialized::ServiceNotYetInitialized(std::string serviceName)
    : m_Message(std::format("The service '{}' has not been initialized yet", serviceName))
{}

const char* ServiceNotYetInitialized::what() const
{
    return m_Message.c_str();
}
