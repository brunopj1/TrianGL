#include "OpenGlException.h"

#include <format>

using namespace Engine::Exceptions::Core;

OpenGlException::OpenGlException(const int error, const char* description)
    : m_Message(std::format("OpenGL error [{}]: {}!", error, description))
{}

const char* OpenGlException::what() const
{
    return m_Message.c_str();
}
