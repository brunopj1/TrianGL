#pragma once

#include "Game/Entity.h"
#include <optional>

class Grid final : public TGL::Entity
{
private:
    glm::uvec2 m_Size;
    std::vector<Entity*> m_Cells;

private:
    TGL::TextureRenderer* m_TextureRenderer = nullptr;

public:
    Grid(glm::uvec2 dimensions);
    ~Grid() override = default;

public:
    glm::uvec2 GetSize() const;
    unsigned int GetCellCount() const;

    Entity* GetCell(const glm::uvec2& position) const;
    void SetCell(const glm::uvec2& position, Entity* entity);

    std::optional<glm::ivec2> GetRandomFreeCell() const;

public:
    void Resize(const glm::uvec2& size);
    void FocusCamera() const;
};
