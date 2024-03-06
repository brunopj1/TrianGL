#include "SingletonNotBeingUsedException.h"

#include <format>

using namespace Engine::Exceptions::Core;

SingletonNotBeingUsedException::SingletonNotBeingUsedException(std::string serviceName, std::string objectName)
    : m_Message(std::format("Invalid operation on object '{}'. Use the service '{}' instead", objectName, serviceName))
{}

const char* SingletonNotBeingUsedException::what() const
{
    return m_Message.c_str();
}
