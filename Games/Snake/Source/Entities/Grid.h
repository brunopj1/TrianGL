#pragma once

#include "Game/Entity.h"
#include <optional>

class Grid final : public Engine::Entity
{
private:
    glm::uvec2 m_Size;
    std::vector<Entity*> m_Cells;

private:
    Engine::TextureRenderer* m_TextureRenderer = nullptr;

public:
    Grid(glm::uvec2 dimensions);
    ~Grid() override = default;

public:
    glm::uvec2 GetSize() const;
    unsigned int GetCellCount() const;

    void Resize(const glm::uvec2& size);

    Entity* GetCell(const glm::uvec2& position) const;
    Entity* SetCell(const glm::uvec2& position, Entity* entity);

    std::optional<glm::ivec2> GetRandomFreeCell() const;
};
