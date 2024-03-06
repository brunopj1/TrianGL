#include "MaterialAttributes.h"

#include "glad/glad.h"

using namespace Engine::Resources;

MaterialAttribute::MaterialAttribute(const int location)
    : m_Location(location)
{}

void MaterialAttribute::Bind() const
{
    if (m_Location == -1) return;
    BindInternal();
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
