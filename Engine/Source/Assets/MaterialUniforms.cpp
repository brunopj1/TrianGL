#include "Core/DataTypes.h"
#include "Core/Internal/RenderLayer.h"
#include <Assets/MaterialUniforms.h>

#include <Assets/Texture.h>
#include <Core/AssetManager.h>
#include <Assets/Internal/Shader.h>

using namespace TGL;

MaterialUniform::MaterialUniform(const Shader* shader, const std::string& name)
    : m_Location(shader->GetUniformLocation(name))
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::AssetManager, MaterialUniform);
}

MaterialUniform::~MaterialUniform()
{
    ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::AssetManager, MaterialUniform);
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
    RenderLayer::SetUniform1i(m_Location, Value);
}

void MaterialUniformImpl<glm::ivec2>::BindInternal() const
{
    RenderLayer::SetUniform2iv(m_Location, Value);
}

void MaterialUniformImpl<glm::ivec3>::BindInternal() const
{
    RenderLayer::SetUniform3iv(m_Location, Value);
}

void MaterialUniformImpl<glm::ivec4>::BindInternal() const
{
    RenderLayer::SetUniform4iv(m_Location, Value);
}

void MaterialUniformImpl<u32>::BindInternal() const
{
    RenderLayer::SetUniform1ui(m_Location, Value);
}

void MaterialUniformImpl<glm::uvec2>::BindInternal() const
{
    RenderLayer::SetUniform2uiv(m_Location, Value);
}

void MaterialUniformImpl<glm::uvec3>::BindInternal() const
{
    RenderLayer::SetUniform3uiv(m_Location, Value);
}

void MaterialUniformImpl<glm::uvec4>::BindInternal() const
{
    RenderLayer::SetUniform4uiv(m_Location, Value);
}

void MaterialUniformImpl<f32>::BindInternal() const
{
    RenderLayer::SetUniform1f(m_Location, Value);
}

void MaterialUniformImpl<glm::vec2>::BindInternal() const
{
    RenderLayer::SetUniform2fv(m_Location, Value);
}

void MaterialUniformImpl<glm::vec3>::BindInternal() const
{
    RenderLayer::SetUniform3fv(m_Location, Value);
}

void MaterialUniformImpl<glm::vec4>::BindInternal() const
{
    RenderLayer::SetUniform4fv(m_Location, Value);
}

void MaterialUniformImpl<glm::mat2>::BindInternal() const
{
    RenderLayer::SetUniformMatrix2fv(m_Location, Value);
}

void MaterialUniformImpl<glm::mat3>::BindInternal() const
{
    RenderLayer::SetUniformMatrix3fv(m_Location, Value);
}

void MaterialUniformImpl<glm::mat4>::BindInternal() const
{
    RenderLayer::SetUniformMatrix4fv(m_Location, Value);
}

SpriteUniform::SpriteUniform(const Shader* shader, const std::string& name)
    : MaterialUniform(shader, name),
      m_MatrixLocation(shader->GetUniformLocation(name + "Matrix")),
      m_ResolutionLocation(shader->GetUniformLocation(name + "Resolution")),
      m_Slot(0), Value(nullptr) // The slot is updated by the spawner
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
    if (Value == nullptr) // If location is -1 the sampler is not being used, so we don't need to unbind
    {
        Sprite::Unbind(m_Slot);
        return;
    }

    if (m_Location != -1)
    {
        Value->Bind(m_Slot);
        RenderLayer::SetUniform1i(m_Location, m_Slot);
    }

    if (m_MatrixLocation != -1)
    {
        glm::mat4* matrix = Value->GetMatrix();

        if (matrix != nullptr)
        {
            RenderLayer::SetUniformMatrix4fv(m_MatrixLocation, *matrix);
        }
        else
        {
            RenderLayer::SetUniformMatrix4fv(m_MatrixLocation, glm::mat4(1.0f));
        }
    }

    if (m_ResolutionLocation != -1)
    {
        RenderLayer::SetUniform2uiv(m_ResolutionLocation, Value->GetResolution());
    }
}
