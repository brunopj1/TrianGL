#include "Snake.h"

#include "Apple.h"
#include "Services/EntityManager.h"
#include "Services/InputSystem.h"
#include "DefaultResources/DefaultMaterial.h"
#include "GameMode/OrderOfExecution.hpp"

// TODO grid class (array and unordered_map)
// TODO grid rendering

using namespace Engine::Services;

Snake::Snake()
    : Entity(true)
{
    m_BodyDirection = m_MoveDirection = {0, 1};

    const auto snakeHead = SpawnEntity<SnakeBody>(glm::ivec2(0, 0));
    m_Body.push_back(snakeHead);

    const auto snakeTail = SpawnEntity<SnakeBody>(glm::ivec2(0, -1));
    m_Body.push_back(snakeTail);
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

void Snake::Move()
{
    const auto headPosition = m_Body.front()->GetPosition();

    const auto lastBody = m_Body.back();
    lastBody->SetPosition(headPosition + m_MoveDirection);

    m_Body.pop_back();
    m_Body.insert(m_Body.begin(), lastBody);

    m_BodyDirection = m_MoveDirection;
}
