#include "Apple.h"

#include "Grid.h"
#include "Components/TextureRenderer.h"
#include "DefaultResources/DefaultMaterial.h"
#include "GameMode/OrderOfExecution.hpp"

using namespace TGL;

Apple::Apple(Grid* grid)
    : Entity(false)
{
    TextureRenderer* texture = AttachComponent<TextureRenderer>();
    texture->GetTransform().SetRotationDeg(45);
    texture->GetTransform().SetScale(0.5f);

    const auto material = texture->UseDefaultMaterial();
    material->GetColorAttr()->SetValue({0.9f, 0.23f, 0.15f, 1.0f});

    RandomizePosition(grid);
}

int Apple::GetOrderOfExecution() const
{
    return static_cast<int>(OrderOfExecution::Food);
}

void Apple::RandomizePosition(Grid* grid)
{
    std::optional<glm::ivec2> freeCell = grid->GetRandomFreeCell();

    if (freeCell.has_value())
    {
        grid->SetCell(freeCell.value(), this);
    }
    else
    {
        Destroy();
    }
}
