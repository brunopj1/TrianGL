#include "MaterialAttributes.h"

#include "Texture.h"
#include "glad/glad.h"

using namespace TGL;

MaterialAttribute::MaterialAttribute(const int location)
    : m_Location(location)
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::MaterialAttribute);
}

MaterialAttribute::~MaterialAttribute()
{
    ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::MaterialAttribute);
}

bool MaterialAttribute::IsValid() const
{
    return m_Location != -1;
}

void MaterialAttribute::Bind() const
{
    if (IsValid())
    {
        BindInternal();
    }
}

TextureMaterialAttribute::TextureMaterialAttribute(const int samplerLocation, const int matrixLocation, const unsigned char slot)
    : MaterialAttribute(samplerLocation), m_MatrixLocation(matrixLocation), m_Value(nullptr), m_Slot(slot) {}

std::shared_ptr<TextureBinding> TextureMaterialAttribute::GetValue() const
{
    return m_Value;
}

void TextureMaterialAttribute::SetValue(std::shared_ptr<TextureBinding> value)
{
    m_Value = std::move(value);
}

bool TextureMaterialAttribute::IsValid() const
{
    return m_Location != -1 || m_MatrixLocation != -1;
}

void TextureMaterialAttribute::BindInternal() const
{
    if (m_Value == nullptr) // If location is -1 the sampler is not being used, so we don't need to unbind
    {
        TextureBinding::Unbind(m_Slot);
        return;
    }

    if (m_Location != -1)
    {
        m_Value->Bind(m_Slot);
        glUniform1i(m_Location, m_Slot);
    }

    if (m_MatrixLocation != -1)
    {
        glm::mat4* matrix = m_Value->GetMatrix();

        if (matrix != nullptr)
        {
            glUniformMatrix4fv(m_MatrixLocation, 1, GL_FALSE, &(*matrix)[0][0]);
        }
        else
        {
            glUniformMatrix4fv(m_MatrixLocation, 1, GL_FALSE, &glm::mat4(1.0f)[0][0]);
        }
    }
}

void IntMaterialAttribute::BindInternal() const
{
    glUniform1i(m_Location, m_Value);
}

void Int2MaterialAttribute::BindInternal() const
{
    glUniform2iv(m_Location, 1, &m_Value[0]);
}

void Int3MaterialAttribute::BindInternal() const
{
    glUniform3iv(m_Location, 1, &m_Value[0]);
}

void Int4MaterialAttribute::BindInternal() const
{
    glUniform4iv(m_Location, 1, &m_Value[0]);
}

void UintMaterialAttribute::BindInternal() const
{
    glUniform1ui(m_Location, m_Value);
}

void Uint2MaterialAttribute::BindInternal() const
{
    glUniform2uiv(m_Location, 1, &m_Value[0]);
}

void Uint3MaterialAttribute::BindInternal() const
{
    glUniform3uiv(m_Location, 1, &m_Value[0]);
}

void FloatMaterialAttribute::BindInternal() const
{
    glUniform1f(m_Location, m_Value);
}

void Float2MaterialAttribute::BindInternal() const
{
    glUniform2fv(m_Location, 1, &m_Value[0]);
}

void Float3MaterialAttribute::BindInternal() const
{
    glUniform3fv(m_Location, 1, &m_Value[0]);
}

void Float4MaterialAttribute::BindInternal() const
{
    glUniform4fv(m_Location, 1, &m_Value[0]);
}

void Mat2MaterialAttribute::BindInternal() const
{
    glUniformMatrix2fv(m_Location, 1, GL_FALSE, &m_Value[0][0]);
}

void Mat3MaterialAttribute::BindInternal() const
{
    glUniformMatrix3fv(m_Location, 1, GL_FALSE, &m_Value[0][0]);
}

void Mat4MaterialAttribute::BindInternal() const
{
    glUniformMatrix4fv(m_Location, 1, GL_FALSE, &m_Value[0][0]);
}
