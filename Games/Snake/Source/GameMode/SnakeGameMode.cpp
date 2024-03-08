#include "SnakeGameMode.h"

#include "Entities/Apple.h"
#include "Entities/Snake.h"
#include "Services/EntityManager.h"
#include "Entities/Camera.h"

using namespace Engine::Services;

SnakeGameMode::SnakeGameMode()
{
    m_Camera = EntityManager::SpawnEntity<Engine::Entities::Camera>(true);

    m_Snake = EntityManager::SpawnEntity<Snake>();

    m_Apple = EntityManager::SpawnEntity<Apple>();
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
