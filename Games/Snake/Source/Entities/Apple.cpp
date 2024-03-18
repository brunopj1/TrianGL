#include "Apple.h"

#include "Grid.h"
#include "Components/TextureRenderer.h"
#include "DefaultResources/DefaultMaterial.h"
#include "Resources/Texture.h"

using namespace TGL;

Apple::Apple(Grid* grid, std::shared_ptr<Texture> spriteSheet)
    : Entity(false), m_SpriteSheet(std::move(spriteSheet))
{
    TextureRenderer* tr = AttachComponent<TextureRenderer>();
    const auto material = tr->UseDefaultMaterial();
    material->Texture->Value = m_SpriteSheet->GetSlice(7);

    RandomizePosition(grid);
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
