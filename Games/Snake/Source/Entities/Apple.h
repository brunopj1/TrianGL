#pragma once

#include "Assets/Texture.h"
#include "Game/Entity.h"
#include "Grid.h"

class Apple final : public TGL::Entity
{
private:
	TGL::SharedPtr<TGL::Texture> m_SpriteSheet;

public:
	Apple(Grid* grid, TGL::SharedPtr<TGL::Texture> spriteSheet);
	~Apple() override = default;

public:
	void RandomizePosition(Grid* grid);
};
