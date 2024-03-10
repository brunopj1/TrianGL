#include "EntityManager.h"

#include "Components/TextureRenderer.h"
#include "Game/GameMode.h"
#include "Game/Entity.h"
#include "Game/Component.h"
#include "Game/Internal/Updatable.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Services;

EntityManager::EntityManager()
{
    s_Instance = this;
}

EntityManager::~EntityManager()
{
    m_GameMode->Destroy();

    while (!m_Entities.empty())
    {
        const auto entity = *m_Entities.begin();
        entity->Destroy();
    }

    s_Instance = nullptr;
}

void EntityManager::Update(const float deltaTime)
{
    for (Game::Internal::Updatable* updatable : m_OnStartQueue)
    {
        updatable->OnStart();
    }
    m_OnStartQueue.clear();

    m_GameMode->OnEarlyUpdate(deltaTime);

    for (Game::Internal::Updatable* updatable : m_OnUpdateQueue)
    {
        if (updatable->m_ShouldUpdate)
        {
            updatable->OnUpdate(deltaTime);
        }
    }

    m_GameMode->OnLateUpdate(deltaTime);
}

void EntityManager::Render() const
{
    for (Game::Internal::Renderable* renderable : m_RenderQueue)
    {
        renderable->Render();
    }
}

void EntityManager::SetGameMode(Game::GameMode* gameMode)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    s_Instance->m_GameMode = gameMode;
}

void EntityManager::AddEntity(Game::Entity* entity)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    s_Instance->m_Entities.insert(entity);

    AddToQueue(entity, s_Instance->m_OnStartQueue);
    AddToQueue(entity, s_Instance->m_OnUpdateQueue);
}

void EntityManager::RemoveEntity(Game::Entity* entity)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    if (const size_t num = s_Instance->m_Entities.erase(entity); num == 0) return;

    std::erase(s_Instance->m_OnStartQueue, entity);
    std::erase(s_Instance->m_OnUpdateQueue, entity);
}

void EntityManager::AddComponent(Game::Component* component)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    s_Instance->m_Components.insert(component);

    AddToQueue(component, s_Instance->m_OnStartQueue);
    AddToQueue(component, s_Instance->m_OnUpdateQueue);

    if (const auto renderable = dynamic_cast<Game::Internal::Renderable*>(component))
    {
        s_Instance->m_RenderQueue.push_back(renderable);
    }
}

void EntityManager::RemoveComponent(Game::Component* component)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    if (const size_t num = s_Instance->m_Components.erase(component); num == 0) return;

    std::erase(s_Instance->m_OnStartQueue, component);
    std::erase(s_Instance->m_OnUpdateQueue, component);

    if (const auto renderable = dynamic_cast<Game::Internal::Renderable*>(component))
    {
        std::erase(s_Instance->m_RenderQueue, renderable);
    }
}

Engine::Game::GameMode* EntityManager::GetGameMode()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_GameMode;
}

std::unordered_set<Engine::Game::Entity*>& EntityManager::GetEntities()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_Entities;
}

std::unordered_set<Engine::Game::Component*>& EntityManager::GetComponents()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_Components;
}

void EntityManager::AddToQueue(Game::Internal::Updatable* updatable, std::vector<Game::Internal::Updatable*>& queue)
{
    const auto order = updatable->GetOrderOfExecution();

    for (auto it = queue.begin(); it != queue.end(); ++it)
    {
        if ((*it)->GetOrderOfExecution() > order)
        {
            queue.insert(it, updatable);
            return;
        }
    }

    queue.push_back(updatable);
}
