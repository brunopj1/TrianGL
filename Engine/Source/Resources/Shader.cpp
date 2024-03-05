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

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
    : m_VertexShaderPath(std::move(vertexShaderPath)), m_FragmentShaderPath(std::move(fragmentShaderPath))
{
    Load();
}

Shader::~Shader()
{
    Free();
}

std::string Shader::GetVertexShaderPath() const
{
    return m_VertexShaderPath;
}

std::string Shader::GetFragmentShaderPath() const
{
    return m_FragmentShaderPath;
}

void Shader::Load()
{
    m_VertexShaderId = CompileShader(m_VertexShaderPath, GL_VERTEX_SHADER);
    m_FragmentShaderId = CompileShader(m_FragmentShaderPath, GL_FRAGMENT_SHADER);

    m_ProgramId = glCreateProgram();
    glAttachShader(m_ProgramId, m_VertexShaderId);
    glAttachShader(m_ProgramId, m_FragmentShaderId);
    glLinkProgram(m_ProgramId);
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

int Shader::CompileShader(const std::string& filePath, const int type)
{
    const std::string shaderSource = ReadShaderFile(filePath);
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

void Shader::Use() const
{
    glUseProgram(m_ProgramId);
}
