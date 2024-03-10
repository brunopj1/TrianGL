#include "SnakeGameMode.h"

#include "Entities/Apple.h"
#include "Entities/Snake.h"
#include "Entities/Camera.h"

using namespace Engine::Game;


SnakeGameMode::SnakeGameMode()
{
    m_Camera = SpawnEntity<Engine::Entities::Camera>(true);

    m_Grid = SpawnEntity<Grid>(glm::uvec2(5, 5));

    m_Snake = SpawnEntity<Snake>();

    m_Apple = SpawnEntity<Apple>();
    m_Apple->GetTransform().TranslateBy({2, 1});
}

void SnakeGameMode::OnLateUpdate(const float deltaTime)
{
    m_TickTimer -= deltaTime;

    if (m_TickTimer <= 0)
    {
        m_TickTimer = m_TickRate;

        m_Snake->Move();
    }
}
