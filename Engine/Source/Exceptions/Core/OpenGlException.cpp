#include "OpenGlException.h"

using namespace Engine::Exceptions::Core;

OpenGlException::OpenGlException(const int error, const char* description)
    : m_Error(error), m_Description(description)
{}

const char* OpenGlException::what() const
{
    return m_Description;
}
