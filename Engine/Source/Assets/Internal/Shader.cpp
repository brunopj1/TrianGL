#include "Core/DataTypes.h"
#include "Core/Services/Backends/RenderBackend.h"
#include "Core/Services/Private/AssetManager.h"
#include "Exceptions/OpenGL/ShaderLinkingException.h"
#include <Assets/Internal/Shader.h>
#include <Exceptions/Common/FileNotFoundException.h>
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

const std::vector<ShaderAttributeInfo>& Shader::GetAttributes() const
{
	return m_Attributes;
}

i32 Shader::GetUniformLocation(const std::string& name) const
{
	const auto it = m_Uniforms.find(name);
	return it != m_Uniforms.end() ? it->second.Location : -1;
}

ShaderDataType Shader::GetUniformDataType(const std::string& name) const
{
	const auto it = m_Uniforms.find(name);
	return it != m_Uniforms.end() ? it->second.DataType : ShaderDataType::INVALID;
}

void Shader::Init()
{
	RenderBackend& renderBackend = RenderBackend::Get();

	const u32 vertexShaderId = CompileShader(m_VertexShader, ShaderType::Vertex, renderBackend);
	const u32 fragmentShaderId = CompileShader(m_FragmentShader, ShaderType::Fragment, renderBackend);

	LinkProgram(renderBackend, vertexShaderId, fragmentShaderId);

	LoadAttributes(renderBackend);
	LoadUniformLocations(renderBackend);
}

void Shader::Free()
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.DeleteProgram(m_ProgramId);
	m_ProgramId = 0;
}

void Shader::LinkProgram(RenderBackend& renderBackend, const u32 vertexShaderId, const u32 fragmentShaderId)
{
	m_ProgramId = renderBackend.CreateProgram();

	renderBackend.AttachShader(m_ProgramId, vertexShaderId);
	renderBackend.AttachShader(m_ProgramId, fragmentShaderId);

	std::string errorLog;
	const bool success = renderBackend.LinkProgram(m_ProgramId, errorLog);

	renderBackend.DetachShader(m_ProgramId, vertexShaderId);
	renderBackend.DeleteShader(vertexShaderId);

	renderBackend.DetachShader(m_ProgramId, fragmentShaderId);
	renderBackend.DeleteShader(fragmentShaderId);

	if (!success)
	{
		renderBackend.DeleteProgram(m_ProgramId);
		throw ShaderLinkingException(errorLog);
	}
}

i32 Shader::CompileShader(const std::string& shaderPath, const ShaderType type, RenderBackend& renderBackend)
{
	const std::string shaderSource = ReadShaderFile(shaderPath);

	const i32 shaderId = renderBackend.CreateShader(type);

	std::string errorLog;
	const bool success = renderBackend.CompileShader(shaderId, shaderSource, errorLog);

	if (!success)
	{
		renderBackend.DeleteShader(shaderId);
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

	std::stringstream stringStream;
	stringStream << file.rdbuf();

	return stringStream.str();
}

void Shader::LoadAttributes(RenderBackend& renderBackend)
{
	m_Attributes = renderBackend.GetShaderAttributes(m_ProgramId);
}

void Shader::LoadUniformLocations(RenderBackend& renderBackend)
{
	const auto uniforms = renderBackend.GetShaderUniforms(m_ProgramId);

	for (const auto& uniform : uniforms)
	{
		m_Uniforms[uniform.Name] = uniform;
	}
}

void Shader::Use() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.UseProgram(m_ProgramId);
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
