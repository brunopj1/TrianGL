#include "ShaderCompilationException.h"

#include "glad/glad.h"
#include <format>

using namespace Engine::Exceptions::Core;

ShaderCompilationException::ShaderCompilationException(const int shaderType, std::string shaderLog)
    : m_Message(std::format("Failed to compile {} shader: {}", shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment", shaderLog))
{}

ShaderCompilationException::ShaderCompilationException(std::string programLog)
    : m_Message(std::format("Failed to link program: {}", programLog))
{}

const char* ShaderCompilationException::what() const
{
    return m_Message.c_str();
}
