#include "SnakeBody.h"

#include "Services/EntityManager.h"
#include "Components/TextureRenderer.h"
#include "DefaultResources/DefaultMaterial.h"

SnakeBody::SnakeBody(const glm::ivec2 position)
    : Entity(false)
{
    GetTransform().SetScale(0.75f);
    SetPosition(position);

    const auto tr = Engine::Services::EntityManager::AttachComponent<Engine::Components::TextureRenderer>(this);
    const auto material = tr->UseDefaultMaterial();
    material->GetColorAttr()->SetValue({0.16f, 0.5f, 0.15f, 1.0f});
}

const glm::ivec2& SnakeBody::GetPosition() const
{
    return m_Position;
}

void SnakeBody::SetPosition(const glm::ivec2& position)
{
    GetTransform().SetPosition(position);
    m_Position = position;
}
