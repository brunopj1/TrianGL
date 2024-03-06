#include "Shader.h"

#include "Exceptions/Common/FileNotFoundException.h"
#include "Exceptions/Common/FileTooBigException.h"
#include "Exceptions/Core/OpenGlException.h"
#include "Exceptions/Core/ShaderCompilationException.h"
#include "glad/glad.h"
#include <codecvt>
#include <fstream>
#include <sstream>

using namespace Engine::Resources;

Shader::Shader(std::string vertexShader, std::string fragmentShader, const bool isFilePath)
    : m_VertexShader(std::move(vertexShader)), m_FragmentShader(std::move(fragmentShader)), m_IsFilePath(isFilePath)
{
    Load();
}

Shader::~Shader()
{
    Free();
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

        throw Exceptions::Core::ShaderCompilationException(logStr);
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

        throw Exceptions::Core::ShaderCompilationException(type, logStr);
    }

    return shaderId;
}

std::string Shader::ReadShaderFile(const std::string& filePath)
{
    const std::ifstream file(filePath);

    if (!file || !file.is_open())
    {
        throw Exceptions::Common::FileNotFoundException(filePath);
    }

    // 64KiB sanity check for shaders:
    if (const auto size = file.gcount(); size > 0x10000)
    {
        throw Exceptions::Common::FileTooBigException(filePath, "64KiB");
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
    // TODO in debug mode give a warning if the location is -1
    const auto it = m_UniformLocations.find(name);
    return it != m_UniformLocations.end() ? it->second : -1;
}

void Shader::Use() const
{
    glUseProgram(m_ProgramId);
}
