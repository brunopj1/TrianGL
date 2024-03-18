#include "MaterialUniforms.h"

#include "Texture.h"
#include "glad/glad.h"

using namespace TGL;

MaterialUniform::MaterialUniform(const int location)
    : m_Location(location)
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::MaterialUniform);
}

MaterialUniform::~MaterialUniform()
{
    ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::MaterialUniform);
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

void IntUniform::BindInternal() const
{
    glUniform1i(m_Location, Value);
}

void Int2Uniform::BindInternal() const
{
    glUniform2iv(m_Location, 1, &Value[0]);
}

void Int3Uniform::BindInternal() const
{
    glUniform3iv(m_Location, 1, &Value[0]);
}

void Int4Uniform::BindInternal() const
{
    glUniform4iv(m_Location, 1, &Value[0]);
}

void UintUniform::BindInternal() const
{
    glUniform1ui(m_Location, Value);
}

void Uint2Uniform::BindInternal() const
{
    glUniform2uiv(m_Location, 1, &Value[0]);
}

void Uint3Uniform::BindInternal() const
{
    glUniform3uiv(m_Location, 1, &Value[0]);
}

void FloatUniform::BindInternal() const
{
    glUniform1f(m_Location, Value);
}

void Float2Uniform::BindInternal() const
{
    glUniform2fv(m_Location, 1, &Value[0]);
}

void Float3Uniform::BindInternal() const
{
    glUniform3fv(m_Location, 1, &Value[0]);
}

void Float4Uniform::BindInternal() const
{
    glUniform4fv(m_Location, 1, &Value[0]);
}

void Mat2Uniform::BindInternal() const
{
    glUniformMatrix2fv(m_Location, 1, GL_FALSE, &Value[0][0]);
}

void Mat3Uniform::BindInternal() const
{
    glUniformMatrix3fv(m_Location, 1, GL_FALSE, &Value[0][0]);
}

void Mat4Uniform::BindInternal() const
{
    glUniformMatrix4fv(m_Location, 1, GL_FALSE, &Value[0][0]);
}

TextureUniform::TextureUniform(const int samplerLocation, const int matrixLocation, const unsigned char slot)
    : MaterialUniform(samplerLocation), m_MatrixLocation(matrixLocation), m_Slot(slot), Value(nullptr) {}

bool TextureUniform::IsValid() const
{
    return m_Location != -1 || m_MatrixLocation != -1;
}

void TextureUniform::BindInternal() const
{
    if (Value == nullptr) // If location is -1 the sampler is not being used, so we don't need to unbind
    {
        TextureBinding::Unbind(m_Slot);
        return;
    }

    if (m_Location != -1)
    {
        Value->Bind(m_Slot);
        glUniform1i(m_Location, m_Slot);
    }

    if (m_MatrixLocation != -1)
    {
        glm::mat4* matrix = Value->GetMatrix();

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
