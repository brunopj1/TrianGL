#include "Apple.h"

#include "Grid.h"
#include "Components/TextureRenderer.h"
#include "DefaultResources/DefaultMaterial.h"
#include "GameMode/OrderOfExecution.hpp"
#include "Resources/Texture.h"

using namespace TGL;

Apple::Apple(Grid* grid, std::shared_ptr<Texture> spriteSheet)
    : Entity(false), m_SpriteSheet(std::move(spriteSheet))
{
    TextureRenderer* tr = AttachComponent<TextureRenderer>();
    const auto material = tr->UseDefaultMaterial();
    material->GetTextureAttr()->SetValue(m_SpriteSheet->GetSlice(7));

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
