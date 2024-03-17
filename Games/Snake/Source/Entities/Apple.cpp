#include "Apple.h"

#include "Grid.h"
#include "Components/TextureRenderer.h"
#include "DefaultResources/DefaultMaterial.h"
#include "GameMode/OrderOfExecution.hpp"
#include "Resources/Texture.h"

using namespace TGL;

Apple::Apple(Grid* grid)
    : Entity(false)
{
    TextureRenderer* tr = AttachComponent<TextureRenderer>();
    tr->GetTransform().SetRotationDeg(45);
    tr->GetTransform().SetScale({-0.5, 0.5f});

    const auto material = tr->UseDefaultMaterial();
    //material->GetColorAttr()->SetValue({0.9f, 0.23f, 0.15f, 1.0f});

    auto params = TextureParameters();
    params.Filter = TextureFilterMode::Nearest;

    const auto texture = Texture::Load("Assets/Textures/test2.png", params);
    texture->CreateSliceGrid({16, 16}, {2, 3}, {4, 12});

    material->GetTextureAttr()->SetValue(texture->GetSlice(3));

    RandomizePosition(grid);
}

int Apple::GetOrderOfExecution() const
{
    return static_cast<int>(OrderOfExecution::Food);
}

void Apple::RandomizePosition(Grid* grid)
{
    const std::optional<glm::ivec2> freeCell = grid->GetRandomFreeCell();

    if (freeCell.has_value())
    {
        grid->SetCell(freeCell.value(), this);
    }
    else
    {
        Destroy();
    }
}
