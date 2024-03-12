#include "SnakeBody.h"

#include "Components/TextureRenderer.h"
#include "DefaultResources/DefaultMaterial.h"

using namespace TGL;

SnakeBody::SnakeBody(Grid* grid, const glm::ivec2& position)
    : Entity(false)
{
    const auto texture = AttachComponent<TextureRenderer>();
    texture->GetTransform().SetScale(0.75f);

    const auto material = texture->UseDefaultMaterial();
    material->GetColorAttr()->SetValue({0.16f, 0.5f, 0.15f, 1.0f});

    grid->SetCell(position, this);
}
