#pragma once
#include "Game/Entity.h"

class SnakeBody final : public Engine::Entity
{
private:
    glm::ivec2 m_Position;

public:
    SnakeBody(glm::ivec2 position);

public:
    const glm::ivec2& GetPosition() const;
    void SetPosition(const glm::ivec2& position);
};
