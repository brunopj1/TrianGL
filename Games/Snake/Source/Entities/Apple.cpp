#include "Apple.h"

#include "Assets/Texture.h"
#include "GameMode/RenderingOrder.h"
#include "Grid.h"
#include "Implementations/Assets/DefaultSpriteMaterial.h"
#include "Implementations/Components/SpriteRenderer.h"

using namespace TGL;

Apple::Apple(Grid* grid, SharedPtr<Texture> spriteSheet)
	: Entity(false), m_SpriteSheet(std::move(spriteSheet))
{
	SpriteRenderer* sr = AttachComponent<SpriteRenderer>();
	sr->SetZIndex(static_cast<i32>(RenderingOrder::Apple));

	const auto material = sr->UseDefaultMaterial();
	material->Sprite->Value = m_SpriteSheet->GetSlice(11);

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
