#include <Game/Transform.h>

#include <glm/gtc/matrix_transform.hpp>

using namespace TGL;

glm::vec2 Transform::GetPosition() const
{
    return m_Position;
}

float Transform::GetRotationRad() const
{
    return m_Rotation;
}

float Transform::GetRotationDeg() const
{
    return m_Rotation * 180.0f / glm::pi<float>();
}

glm::vec2 Transform::GetScale() const
{
    return m_Scale;
}

void Transform::SetPosition(const glm::vec2& newPosition)
{
    m_Position = newPosition;
    m_WasModified = true;
}

void Transform::SetRotationRad(const float newRotation)
{
    m_Rotation = newRotation;
    m_WasModified = true;
}

void Transform::SetRotationDeg(const float newRotation)
{
    m_Rotation = newRotation * glm::pi<float>() / 180.0f;
    m_WasModified = true;
}

void Transform::SetScale(const glm::vec2& newScale)
{
    m_Scale = newScale;
    m_WasModified = true;
}

void Transform::SetScale(float newScale)
{
    m_Scale = {newScale, newScale};
    m_WasModified = true;
}

void Transform::TranslateBy(const glm::vec2& translation)
{
    m_Position += translation;
    m_WasModified = true;
}

void Transform::RotateByRad(const float rotation)
{
    m_Rotation += rotation;
    m_WasModified = true;
}

void Transform::RotateByDeg(const float rotation)
{
    m_Rotation += rotation * glm::pi<float>() / 180.0f;
    m_WasModified = true;
}

void Transform::ScaleBy(const glm::vec2& scale)
{
    m_Scale *= scale;
    m_WasModified = true;
}

void Transform::ScaleBy(const float scale)
{
    m_Scale *= scale;
    m_WasModified = true;
}

glm::mat4 Transform::GetTransformMatrix()
{
    if (m_WasModified)
    {
        const glm::mat4 translateMatrix = translate(glm::mat4(1.0f), glm::vec3(m_Position, 0.0f));
        const glm::mat4 rotateMatrix = rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        const glm::mat4 scaleMatrix = scale(glm::mat4(1.0f), glm::vec3(m_Scale, 1.0f));

        m_TransformMatrix = translateMatrix * rotateMatrix * scaleMatrix;
    }

    return m_TransformMatrix;
}
