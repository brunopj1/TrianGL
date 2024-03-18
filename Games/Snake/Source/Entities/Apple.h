#pragma once

#include "Game/Entity.h"
#include "Resources/Texture.h"
#include "Grid.h"

class Apple final : public TGL::Entity
{
private:
    std::shared_ptr<TGL::Texture> m_SpriteSheet;

public:
    Apple(Grid* grid, std::shared_ptr<TGL::Texture> spriteSheet);
    ~Apple() override = default;

public:
    void RandomizePosition(Grid* grid);
};
