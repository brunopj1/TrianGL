#include "Core/DataTypes.h"
#include "Core/Internal/RenderLayer.h"
#include <Assets/Internal/Shader.h>
#include <Exceptions/Common/FileNotFoundException.h>
#include <Exceptions/Common/FileTooBigException.h>
#include <Exceptions/OpenGL/ShaderCompilationException.h>
#include <fstream>
#include <sstream>

using namespace TGL;

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
	: m_VertexShader(std::move(vertexShaderPath)), m_FragmentShader(std::move(fragmentShaderPath))
{
	// Init() and Free() cannot be called in the constructor and destructor
	// because sometimes we create fake Shader objects to access the unordered_map
	// These methods are called by the TGL::AssetManager
}

void Shader::Init()
{
	m_VertexShaderId = CompileShader(m_VertexShader, ShaderType::Vertex);
	m_FragmentShaderId = CompileShader(m_FragmentShader, ShaderType::Fragment);

	LinkProgram();

	LoadUniformLocations();
}

void Shader::Free()
{
	RenderLayer::DeleteShader(m_VertexShaderId);
	m_VertexShaderId = 0;

	RenderLayer::DeleteShader(m_FragmentShaderId);
	m_FragmentShaderId = 0;

	RenderLayer::DeleteProgram(m_ProgramId);
	m_ProgramId = 0;
}

void Shader::LinkProgram()
{
	m_ProgramId = RenderLayer::CreateProgram();

	RenderLayer::AttachShader(m_ProgramId, m_VertexShaderId);
	RenderLayer::AttachShader(m_ProgramId, m_FragmentShaderId);

	std::string errorLog;
	const bool success = RenderLayer::LinkProgram(m_ProgramId, errorLog);

	if (!success)
	{
		throw ShaderCompilationException(errorLog);
	}
}

i32 Shader::CompileShader(const std::string& shaderPath, const ShaderType type)
{
	const std::string shaderSource = ReadShaderFile(shaderPath);

	const i32 shaderId = RenderLayer::CreateShader(type);

	std::string errorLog;
	const bool success = RenderLayer::CompileShader(shaderId, shaderSource, errorLog);

	if (!success)
	{
		throw ShaderCompilationException(type == ShaderType::Vertex, errorLog);
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

	std::stringstream stringStream;
	stringStream << file.rdbuf();

	return stringStream.str();
}

void Shader::LoadUniformLocations()
{
	const auto uniforms = RenderLayer::GetShaderUniforms(m_ProgramId);

	for (const auto& uniform : uniforms)
	{
		m_UniformLocations[uniform.Name] = uniform.Location;
	}
}

i32 Shader::GetUniformLocation(const std::string& name) const
{
	const auto it = m_UniformLocations.find(name);
	return it != m_UniformLocations.end() ? it->second : -1;
}

void Shader::Use() const
{
	RenderLayer::UseProgram(m_ProgramId);
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
	return shader1->m_VertexShader == shader2->m_VertexShader && shader1->m_FragmentShader == shader2->m_FragmentShader;
}
