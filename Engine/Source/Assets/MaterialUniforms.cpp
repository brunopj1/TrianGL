﻿#include "Core/DataTypes.h"
#include "Core/Services/Backends/RenderBackend.h"
#include "Rendering/Animator.h"
#include <Assets/Internal/Shader.h>
#include <Assets/MaterialUniforms.h>
#include <Core/Services/Private/AssetManager.h>

using namespace TGL;

MaterialUniform::MaterialUniform(const Shader* shader, const std::string& name)
	: m_Location(shader->GetUniformLocation(name))
{
	ASSERT_ASSET_FACTORY_CONSTRUCTOR(MaterialUniform);
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
void MaterialUniformImpl<i32>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform1i(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::ivec2>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform2i(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::ivec3>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform3i(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::ivec4>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform4i(m_Location, Value);
}

template <>
void MaterialUniformImpl<u32>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform1ui(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::uvec2>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform2ui(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::uvec3>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform3ui(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::uvec4>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform4ui(m_Location, Value);
}

template <>
void MaterialUniformImpl<f32>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform1f(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::vec2>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform2f(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::vec3>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform3f(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::vec4>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniform4f(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::mat2>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniformMatrix2f(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::mat3>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniformMatrix3f(m_Location, Value);
}

template <>
void MaterialUniformImpl<glm::mat4>::BindInternal() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetUniformMatrix4f(m_Location, Value);
}

SpriteUniform::SpriteUniform(const Shader* shader, const std::string& name)
	: MaterialUniform(shader, name), m_MatrixLocation(shader->GetUniformLocation(name + "Matrix")), m_ResolutionLocation(shader->GetUniformLocation(name + "Resolution"))
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
