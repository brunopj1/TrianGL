#include "Core/Internal/RenderLayer.h"
#include <Implementations/Components/SpriteRenderer.h>

#include <Game/Entity.h>
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

    if (const i32 zIndex = GetZIndex(); zIndex != 0)
    {
        modelMatrix = translate(modelMatrix, glm::vec3(0.0f, 0.0f, static_cast<f32>(zIndex)));
    }

    m_Material->Use(modelMatrix);

    const AssetManager& assetManager = AssetManager::Get();
    RenderLayer::DrawElements(assetManager.GetQuadVao(), assetManager.GetQuadEbo(), 6);
}
