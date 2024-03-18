﻿#include "Snake.h"

#include <utility>

#include "Apple.h"
#include "Core/InputSystem.h"
#include "DefaultResources/DefaultMaterial.h"
#include "GameMode/OrderOfExecution.hpp"

using namespace TGL;

Snake::Snake(Grid* grid, std::shared_ptr<Texture> spriteSheet, const glm::ivec2& position, const glm::ivec2& direction)
    : Entity(true), m_SpriteSheet(std::move(spriteSheet))
{
    m_BodyDirection = m_MoveDirection = direction;

    SpawnHead(grid, position - direction);
    SpawnHead(grid, position);
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
        m_Body.front()->Modify(SnakeBodyType::Head, m_MoveDirection);
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
        DestroyTailEnd(grid);
        SpawnHead(grid, nextPosition);
        UpdateTail();
    }
    // Hit snake
    else if (const SnakeBody* hitBody = hitEntity->As<SnakeBody>(); hitBody != nullptr)
    {
        DestroyTail(grid, hitBody);
        SpawnHead(grid, nextPosition);
        UpdateTail();
    }
    // Hit apple
    else if (Apple* hitApple = hitEntity->As<Apple>(); hitApple != nullptr)
    {
        SpawnHead(grid, nextPosition);
        hitApple->RandomizePosition(grid);
    }

    m_BodyDirection = m_MoveDirection;
}

void Snake::SpawnHead(Grid* grid, const glm::ivec2& position)
{
    const auto snakeBody = SpawnEntity<SnakeBody>(grid, m_SpriteSheet, position, m_MoveDirection);
    m_Body.insert(m_Body.begin(), snakeBody);

    if (const auto bodySize = m_Body.size(); bodySize > 1)
    {
        m_Body[1]->Modify(bodySize == 2 ? SnakeBodyType::Tail : SnakeBodyType::Body);
    }
}

void Snake::DestroyTailEnd(Grid* grid)
{
    SnakeBody* body = m_Body.back();
    m_Body.pop_back();

    grid->SetCell(body->GetTransform().GetPosition(), nullptr);
    body->Destroy();
}

void Snake::DestroyTail(Grid* grid, const SnakeBody* firstBody)
{
    while (true)
    {
        SnakeBody* body = m_Body.back();
        m_Body.pop_back();

        grid->SetCell(body->GetTransform().GetPosition(), nullptr);
        body->Destroy();

        if (body == firstBody) break;
    }
}

void Snake::UpdateTail() const
{
    const auto bodySize = m_Body.size();
    SnakeBody* tailEnd = m_Body[bodySize - 1];
    SnakeBody* preTailEnd = m_Body[bodySize - 2];

    const glm::ivec2 newDirection = preTailEnd->GetTransform().GetPosition() - tailEnd->GetTransform().GetPosition();

    tailEnd->Modify(SnakeBodyType::Tail, newDirection, newDirection);
}
