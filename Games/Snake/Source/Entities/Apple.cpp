#include "Apple.h"

#include "Grid.h"
#include "Implementations/Components/SpriteRenderer.h"
#include "Implementations/Assets/DefaultSpriteMaterial.h"
#include "Assets/Texture.h"

using namespace TGL;

Apple::Apple(Grid* grid, SharedPtr<Texture> spriteSheet)
    : Entity(false), m_SpriteSheet(std::move(spriteSheet))
{
    SpriteRenderer* sr = AttachComponent<SpriteRenderer>();
    const auto material = sr->UseDefaultMaterial();
    material->Sprite->Value = m_SpriteSheet->GetSlice(7);

    RandomizePosition(grid);
}

void Apple::RandomizePosition(Grid* grid)
{
    const glm::uvec2 currentPos = GetTransform().GetPosition();
    if (grid->GetCell(currentPos) == this)
    {
        grid->SetCell(currentPos, nullptr);
    }
    
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
