#include "Core/DataTypes.h"
#include "Core/Services/Backends/RenderBackend.h"
#include "Material.h"
#include "Rendering/Animator.h"
#include <Assets/Internal/Shader.h>
#include <Assets/MaterialUniforms.h>
#include <Core/Services/Private/AssetManager.h>
#include <utility>

using namespace TGL;

MaterialUniform::MaterialUniform(const Shader* shader, const std::vector<MaterialUniform*>& existingUniforms, const std::string& name, const ShaderDataType dataType)
	: m_Location(shader->GetUniformLocation(name))
{
	ASSERT_ASSET_FACTORY_CONSTRUCTOR(MaterialUniform);

	// Validate the data type
	if (dataType != shader->GetUniformDataType(name))
	{
		m_Location = -1;
	}

	// Check if this uniform was already created
	if (m_Location != -1)
	{
		for (const auto uniform : existingUniforms)
		{
			if (uniform->m_Location == m_Location)
			{
				m_Location = -1;
				break;
			}
		}
	}
}

MaterialUniform::~MaterialUniform()
{
	ASSERT_ASSET_FACTORY_DESTRUCTOR();
}

bool MaterialUniform::IsValid() const
{
	return m_Location != -1;
}

void MaterialUniform::Bind() const
{
	if (IsValid())
	{
		BindInternal();
	}
}

template <>
void MaterialUniformImpl<i32, ShaderDataType::INT>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform1i(m_Location, Value);
}

template <>
void MaterialUniformImpl<u32, ShaderDataType::UINT>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform1ui(m_Location, Value);
}

template <>
void MaterialUniformImpl<f32, ShaderDataType::FLOAT>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform1f(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::ivec2, ShaderDataType::IVEC2>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform2i(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::ivec3, ShaderDataType::IVEC3>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform3i(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::ivec4, ShaderDataType::IVEC4>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform4i(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::uvec2, ShaderDataType::UVEC2>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform2ui(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::uvec3, ShaderDataType::UVEC3>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform3ui(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::uvec4, ShaderDataType::UVEC4>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform4ui(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::vec2, ShaderDataType::FVEC2>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform2f(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::vec3, ShaderDataType::FVEC3>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform3f(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::vec4, ShaderDataType::FVEC4>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform4f(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::mat2, ShaderDataType::MAT2>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniformMatrix2f(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::mat3, ShaderDataType::MAT3>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniformMatrix3f(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::mat4, ShaderDataType::MAT4>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniformMatrix4f(m_Location, Value);
}

SpriteUniform::SpriteUniform(const Shader* shader, const std::vector<MaterialUniform*>& existingUniforms, const std::string& name)
	: MaterialUniform(shader, existingUniforms, name, ShaderDataType::SAMPLER2D),
	  m_MatrixLocation(shader->GetUniformLocation(name + "Matrix")),
	  m_ResolutionLocation(shader->GetUniformLocation(name + "Resolution"))
{}

bool SpriteUniform::HasValue() const
{
	return Value != nullptr;
}

bool SpriteUniform::IsValid() const
{
	return m_Location != -1 || m_MatrixLocation != -1 || m_ResolutionLocation != -1;
}

void SpriteUniform::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();

	if (m_Location != -1 && Value != nullptr)
	{
		const bool isBound = Value->Bind(m_Slot);
		renderBackend.SetUniform1i(m_Location, m_Slot);

		if (!isBound)
		{
			Sprite::Unbind(m_Slot);
		}
	}

	if (m_MatrixLocation != -1)
	{
		const auto value = Value != nullptr ? Value->GetMatrix() : glm::mat4(1.0f);
		renderBackend.SetUniformMatrix4f(m_MatrixLocation, value);
	}

	if (m_ResolutionLocation != -1)
	{
		const auto value = Value != nullptr ? Value->GetResolution() : glm::uvec2(0);
		renderBackend.SetUniform2ui(m_ResolutionLocation, value);
	}
}
