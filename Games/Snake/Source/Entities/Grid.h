#pragma once

#include "Game/Entity.h"
#include "Memory/SharedPtr.h"
#include "Util/RandomNumberGenerator.h"
#include <optional>

class Grid final : public TGL::Entity
{
private:
    glm::uvec2 m_Size;
    std::vector<Entity*> m_Cells;
    TGL::SharedPtr<TGL::Texture> m_SpriteSheet;
    TGL::RandomNumberGenerator m_Random;

private:
    TGL::SpriteRenderer* m_SpriteRenderer = nullptr;

public:
    Grid(TGL::SharedPtr<TGL::Texture> spriteSheet, glm::uvec2 dimensions);
    ~Grid() override = default;

public:
    glm::uvec2 GetSize() const;
    unsigned int GetCellCount() const;

    Entity* GetCell(const glm::uvec2& position) const;
    void SetCell(const glm::uvec2& position, Entity* entity);

    std::optional<glm::ivec2> GetRandomFreeCell();

public:
    void Resize(const glm::uvec2& size);
    void FocusCamera() const;
};
