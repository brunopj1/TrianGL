#include "Assets/Internal/Quad.h"
#include <Implementations/Components/SpriteRenderer.h>

#include <Game/Entity.h>
#include <glad/glad.h>
#include <Assets/Material.h>
#include <Implementations/Assets/DefaultSpriteMaterial.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace TGL;

SpriteRenderer::SpriteRenderer(SharedPtr<Material> material)
    : Component(false), m_Material(std::move(material))
{}

Transform& SpriteRenderer::GetTransform()
{
    return m_Transform;
}

const Transform& SpriteRenderer::GetTransform() const
{
    return m_Transform;
}

SharedPtr<Material> SpriteRenderer::GetMaterial() const
{
    return m_Material;
}

void SpriteRenderer::SetMaterial(SharedPtr<Material> material)
{
    m_Material = std::move(material);
}

SharedPtr<DefaultSpriteMaterial> SpriteRenderer::UseDefaultMaterial()
{
    auto defaultMaterial = Material::CreateInstanceOf<DefaultSpriteMaterial>();
    m_Material = defaultMaterial;
    return defaultMaterial;
}

glm::vec2 SpriteRenderer::GetPivot() const
{
    return m_Pivot;
}

void SpriteRenderer::SetPivot(const glm::vec2& pivot)
{
    m_Pivot = pivot;
}

void SpriteRenderer::Render() const
{
    if (m_Material == nullptr) return;

    const glm::mat4 parentModelMatrix = GetParent()->GetTransform().GetTransformMatrix();
    const glm::mat4 rendererModelMatrix = GetTransform().GetTransformMatrix();

    glm::mat4 modelMatrix = parentModelMatrix * rendererModelMatrix;

    if (m_Pivot != glm::vec2(0.5f))
    {
        const glm::vec3 sign = glm::sign(glm::vec3(modelMatrix[0][0], modelMatrix[1][1], 1));

        modelMatrix = translate(modelMatrix, glm::vec3(0.5f - m_Pivot, 0.0f) * sign);
    }

    if (const int zIndex = GetZIndex(); zIndex != 0)
    {
        modelMatrix = translate(modelMatrix, glm::vec3(0.0f, 0.0f, static_cast<float>(zIndex)));
    }

    m_Material->Use(modelMatrix);

    glBindVertexArray(Quad::s_QuadVao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Quad::s_QuadEbo);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}
