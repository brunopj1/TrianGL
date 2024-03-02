#include "FailedToInitializeEngineException.h"

using namespace Engine::Exceptions::Core;

FailedToInitializeEngineException::FailedToInitializeEngineException(std::string message)
    : m_Message(std::move(message))
{}

const char* FailedToInitializeEngineException::what() const
{
    return m_Message.c_str();
}
