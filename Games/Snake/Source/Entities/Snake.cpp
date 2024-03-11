#include "Snake.h"

#include "Apple.h"
#include "Core/InputSystem.h"
#include "DefaultResources/DefaultMaterial.h"
#include "GameMode/OrderOfExecution.hpp"

using namespace Engine;

Snake::Snake(Grid* grid, const glm::ivec2& position, const glm::ivec2& direction)
    : Entity(true)
{
    m_BodyDirection = m_MoveDirection = direction;


    SpawnBody(grid, position);
}

int Snake::GetOrderOfExecution() const
{
    return static_cast<int>(OrderOfExecution::Snake);
}

void Snake::OnUpdate(const float deltaTime)
{
    glm::ivec2 direction = {0, 0};

    if (InputSystem::IsKeyDown(KeyCode::W)) direction = {0, 1};
    if (InputSystem::IsKeyDown(KeyCode::S)) direction = {0, -1};
    if (InputSystem::IsKeyDown(KeyCode::A)) direction = {-1, 0};
    if (InputSystem::IsKeyDown(KeyCode::D)) direction = {1, 0};

    if (direction != glm::ivec2(0) && direction != m_MoveDirection && direction != -m_BodyDirection)
    {
        m_MoveDirection = direction;
    }
}

void Snake::Move(Grid* grid)
{
    const glm::uvec2 gridSize = grid->GetSize();
    const glm::ivec2 headPosition = m_Body.front()->GetTransform().GetPosition();

    glm::ivec2 nextPosition = headPosition + m_MoveDirection;
    nextPosition.x = (nextPosition.x + gridSize.x) % gridSize.x;
    nextPosition.y = (nextPosition.y + gridSize.y) % gridSize.y;

    Entity* hitEntity = grid->GetCell(nextPosition);

    // No hit
    if (hitEntity == nullptr || hitEntity == m_Body.back())
    {
        DestroyLastBody(grid);
        SpawnBody(grid, nextPosition);
    }
    // Hit snake
    else if (const SnakeBody* hitBody = hitEntity->As<SnakeBody>(); hitBody != nullptr)
    {
        DestroyTail(grid, hitBody);
        SpawnBody(grid, nextPosition);
    }
    // Hit apple
    else if (Apple* hitApple = hitEntity->As<Apple>(); hitApple != nullptr)
    {
        SpawnBody(grid, nextPosition);
        hitApple->RandomizePosition(grid);
    }
}

void Snake::SpawnBody(Grid* grid, const glm::ivec2& position)
{
    const auto snakeBody = SpawnEntity<SnakeBody>(grid, position);
    m_Body.insert(m_Body.begin(), snakeBody);

    m_BodyDirection = m_MoveDirection;
}

void Snake::DestroyLastBody(Grid* grid)
{
    SnakeBody* body = m_Body.back();
    m_Body.pop_back();

    grid->SetCell(body->GetTransform().GetPosition(), nullptr);
    body->Destroy();
}

void Snake::DestroyTail(Grid* grid, const SnakeBody* from)
{
    while (true)
    {
        SnakeBody* body = m_Body.back();
        m_Body.pop_back();

        grid->SetCell(body->GetTransform().GetPosition(), nullptr);
        body->Destroy();

        if (body == from) break;
    }
}
