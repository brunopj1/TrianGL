#include "Shader.h"

#include "Exceptions/Common/FileNotFoundException.hpp"
#include "Exceptions/Common/FileTooBigException.hpp"
#include "Exceptions/OpenGL/ShaderCompilationException.hpp"
#include "glad/glad.h"
#include "Util/Macros/SingletonMacros.hpp"
#include <codecvt>
#include <fstream>
#include <sstream>

using namespace TGL;

Shader::Shader(std::string vertexShader, std::string fragmentShader, const bool isFilePath)
    : m_VertexShader(std::move(vertexShader)), m_FragmentShader(std::move(fragmentShader)), m_IsFilePath(isFilePath)
{
    // Load() and Free() cannot be called in the constructor and destructor
    // because sometimes we create fake Shader objects to acess the unordered_map
    // These methods are called by the TGL::ResourceManager
}

void Shader::Load()
{
    m_VertexShaderId = CompileShader(m_VertexShader, GL_VERTEX_SHADER);
    m_FragmentShaderId = CompileShader(m_FragmentShader, GL_FRAGMENT_SHADER);

    LinkProgram();

    LoadUniformLocations();
}

void Shader::Free()
{
    glDeleteShader(m_VertexShaderId);
    m_VertexShaderId = 0;

    glDeleteShader(m_FragmentShaderId);
    m_FragmentShaderId = 0;

    glDeleteProgram(m_ProgramId);
    m_ProgramId = 0;
}

void Shader::LinkProgram()
{
    m_ProgramId = glCreateProgram();

    glAttachShader(m_ProgramId, m_VertexShaderId);
    glAttachShader(m_ProgramId, m_FragmentShaderId);

    glLinkProgram(m_ProgramId);

    int success = 0;
    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);

    if (success == 0)
    {
        int logLength = 0;
        glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &logLength);

        char* log = new char[logLength + 1];
        glGetProgramInfoLog(m_ProgramId, logLength, nullptr, log);

        const std::string logStr = log;
        delete[] log;

        throw ShaderCompilationException(logStr);
    }
}

int Shader::CompileShader(const std::string& shader, const int type) const
{
    const std::string shaderSource = m_IsFilePath ? ReadShaderFile(shader) : shader;
    const char* shaderSourcePtr = shaderSource.c_str();

    const int shaderId = glCreateShader(type);
    glShaderSource(shaderId, 1, &shaderSourcePtr, nullptr);
    glCompileShader(shaderId);

    int success = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (success == 0)
    {
        int logLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

        char* log = new char[logLength + 1];
        glGetShaderInfoLog(shaderId, logLength, nullptr, log);

        const std::string logStr = log;
        delete[] log;

        throw ShaderCompilationException(type, logStr);
    }

    return shaderId;
}

std::string Shader::ReadShaderFile(const std::string& filePath)
{
    const std::ifstream file(filePath);

    if (!file || !file.is_open())
    {
        throw FileNotFoundException(filePath);
    }

    // 64KiB sanity check for shaders:
    if (const auto size = file.gcount(); size > 0x10000)
    {
        throw FileTooBigException(filePath, "64KiB");
    }

    std::stringstream sstr;
    sstr << file.rdbuf();

    return sstr.str();
}

void Shader::LoadUniformLocations()
{
    int count = 0;
    glGetProgramiv(m_ProgramId, GL_ACTIVE_UNIFORMS, &count);

    GLint size;
    GLenum type;

    constexpr GLsizei bufSize = 1024;
    // ReSharper disable once CppTooWideScope
    GLchar name[bufSize];
    GLsizei length;

    for (int i = 0; i < count; i++)
    {
        glGetActiveUniform(m_ProgramId, i, bufSize, &length, &size, &type, name);
        m_UniformLocations[name] = glGetUniformLocation(m_ProgramId, name);
    }
}

int Shader::GetUniformLocation(const std::string& name) const
{
    const auto it = m_UniformLocations.find(name);
    return it != m_UniformLocations.end() ? it->second : -1;
}

void Shader::Use() const
{
    glUseProgram(m_ProgramId);
}

std::size_t ShaderHash::operator()(const Shader* shader) const
{
    const auto hash1 = std::hash<std::string>{}(shader->m_VertexShader);
    const auto hash2 = std::hash<std::string>{}(shader->m_FragmentShader);

    // Combine the hash values using a simple hash function
    return hash1 ^ hash2;
}

bool ShaderEqual::operator()(const Shader* shader1, const Shader* shader2) const
{
    return shader1->m_IsFilePath == shader2->m_IsFilePath &&
        shader1->m_VertexShader == shader2->m_VertexShader &&
        shader1->m_FragmentShader == shader2->m_FragmentShader;
}
