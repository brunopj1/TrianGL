#include "MaterialAttributes.h"

#include "Texture.h"
#include "glad/glad.h"

using namespace TGL;

MaterialAttribute::MaterialAttribute(const int location)
    : m_Location(location)
{}

bool MaterialAttribute::IsValid() const
{
    return m_Location != -1;
}

void MaterialAttribute::Bind() const
{
    if (m_Location == -1) return;
    BindInternal();
}

TextureMaterialAttribute::TextureMaterialAttribute(const int location, const unsigned slot)
    : MaterialAttribute(location), m_Value(nullptr), m_Slot(slot) {}

std::shared_ptr<Texture> TextureMaterialAttribute::GetValue() const
{
    return m_Value;
}

void TextureMaterialAttribute::SetValue(std::shared_ptr<Texture> value)
{
    m_Value = std::move(value);
}

unsigned TextureMaterialAttribute::GetSlot() const
{
    return m_Slot;
}

void TextureMaterialAttribute::SetSlot(const unsigned slot)
{
    m_Slot = slot;
}

void TextureMaterialAttribute::BindInternal() const
{
    if (m_Value == nullptr) return;
    m_Value->Bind(m_Slot);
    glUniform1i(m_Location, m_Slot);
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
