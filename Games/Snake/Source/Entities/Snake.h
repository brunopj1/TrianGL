#pragma once

#include "Grid.h"
#include "SnakeBody.h"
#include "Game/Entity.h"

class Snake final : public TGL::Entity
{
private:
    glm::ivec2 m_BodyDirection;
    glm::ivec2 m_MoveDirection;

    std::vector<SnakeBody*> m_Body;

public:
    Snake(Grid* grid, const glm::ivec2& position, const glm::ivec2& direction);
    ~Snake() override = default;

protected:
    int GetOrderOfExecution() const override;

protected:
    void OnUpdate(float deltaTime) override;

public:
    void Move(Grid* grid); // Returns true if the apple was eaten

private:
    void SpawnBody(Grid* grid, const glm::ivec2& position);

    void DestroyLastBody(Grid* grid);
    void DestroyTail(Grid* grid, const SnakeBody* from);
};
