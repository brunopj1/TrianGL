﻿#include "Core/DataTypes.h"
#include <Assets/Internal/Shader.h>

#include <Exceptions/Common/FileNotFoundException.h>
#include <Exceptions/Common/FileTooBigException.h>
#include <Exceptions/OpenGL/ShaderCompilationException.h>
#include <glad/glad.h>
#include <Internal/Asserts/ApplicationAsserts.h>
#include <codecvt>
#include <fstream>
#include <sstream>

using namespace TGL;

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
    : m_VertexShader(std::move(vertexShaderPath)), m_FragmentShader(std::move(fragmentShaderPath))
{
    // Init() and Free() cannot be called in the constructor and destructor
    // because sometimes we create fake Shader objects to acess the unordered_map
    // These methods are called by the TGL::AssetManager
}

void Shader::Init()
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

    i32 success = 0;
    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &success);

    if (success == 0)
    {
        i32 logLength = 0;
        glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &logLength);

        char* log = new char[logLength + 1];
        glGetProgramInfoLog(m_ProgramId, logLength, nullptr, log);

        const std::string logStr = log;
        delete[] log;

        throw ShaderCompilationException(logStr);
    }
}

i32 Shader::CompileShader(const std::string& shaderPath, const i32 type)
{
    const std::string shaderSource = ReadShaderFile(shaderPath);
    const char* shaderSourcePtr = shaderSource.c_str();

    const i32 shaderId = glCreateShader(type);
    glShaderSource(shaderId, 1, &shaderSourcePtr, nullptr);
    glCompileShader(shaderId);

    i32 success = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (success == 0)
    {
        i32 logLength = 0;
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
    i32 count = 0;
    glGetProgramiv(m_ProgramId, GL_ACTIVE_UNIFORMS, &count);

    i32 size;
    u32 type;

    constexpr GLsizei bufSize = 1024;
    // ReSharper disable once CppTooWideScope
    char name[bufSize];
    i32 length;

    for (i32 i = 0; i < count; i++)
    {
        glGetActiveUniform(m_ProgramId, i, bufSize, &length, &size, &type, name);
        m_UniformLocations[name] = glGetUniformLocation(m_ProgramId, name);
    }
}

i32 Shader::GetUniformLocation(const std::string& name) const
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
    return
        shader1->m_VertexShader == shader2->m_VertexShader &&
        shader1->m_FragmentShader == shader2->m_FragmentShader;
}
