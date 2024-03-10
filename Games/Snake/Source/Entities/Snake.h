#pragma once

#include "SnakeBody.h"
#include "Game/Entity.h"

class Snake final : public Engine::Entity
{
private:
    glm::ivec2 m_BodyDirection;
    glm::ivec2 m_MoveDirection;

    std::vector<SnakeBody*> m_Body;

public:
    Snake();
    ~Snake() override = default;

protected:
    int GetOrderOfExecution() const override;

protected:
    void OnUpdate(float deltaTime) override;

public:
    void Move();
};
