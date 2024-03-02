#include "EntityManager.h"

#include "Game/GameMode.h"
#include "Game/Entity.h"

using namespace Engine::Core;

EntityManager::EntityManager()
{
    s_Instance = this;
}

EntityManager::~EntityManager()
{
    for (const Game::Entity* entity : m_Entities)
    {
        delete entity;
    }

    m_Entities.clear();

    s_Instance = nullptr;
}

EntityManager* EntityManager::GetInstance()
{
    return s_Instance;
}

void EntityManager::Terminate()
{
    DestroyGameMode();

    for (const Game::Entity* entity : m_Entities)
    {
        delete entity;
    }

    m_Entities.clear();
}

Engine::Game::GameMode* EntityManager::GetGameMode() const
{
    return m_GameMode;
}

void EntityManager::DestroyGameMode()
{
    delete m_GameMode;
    m_GameMode = nullptr;
}

void EntityManager::DestroyEntity(const Game::Entity* entity)
{
    for (auto it = m_Entities.begin(); it != m_Entities.end(); ++it)
    {
        if (*it == entity)
        {
            m_Entities.erase(it);
            delete *it;
            return;
        }
    }
}
