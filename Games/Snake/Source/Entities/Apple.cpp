#include "Apple.h"

#include "Grid.h"
#include "Implementations/Components/SpriteRenderer.h"
#include "Implementations/Assets/DefaultMaterial.h"
#include "Assets/Texture.h"

using namespace TGL;

Apple::Apple(Grid* grid, std::shared_ptr<Texture> spriteSheet)
    : Entity(false), m_SpriteSheet(std::move(spriteSheet))
{
    SpriteRenderer* sr = AttachComponent<SpriteRenderer>();
    const auto material = sr->UseDefaultMaterial();
    material->Sprite->Value = m_SpriteSheet->GetSlice(7);

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
