#include "EntityManager.h"

#include "Components/TextureRenderer.h"
#include "Game/GameMode.h"
#include "Game/Entity.h"
#include "Game/Component.h"
#include "Game/Internal/Updatable.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine;

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
    for (Updatable* updatable : m_OnStartQueue)
    {
        updatable->OnStart();
    }
    m_OnStartQueue.clear();

    m_GameMode->OnEarlyUpdate(deltaTime);

    for (Updatable* updatable : m_OnUpdateQueue)
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
    for (Renderable* renderable : m_RenderQueue)
    {
        renderable->Render();
    }
}

void EntityManager::SetGameMode(GameMode* gameMode)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    s_Instance->m_GameMode = gameMode;
}

void EntityManager::AddEntity(Entity* entity)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    s_Instance->m_Entities.insert(entity);

    AddToQueue(entity, s_Instance->m_OnStartQueue);
    AddToQueue(entity, s_Instance->m_OnUpdateQueue);
}

bool EntityManager::RemoveEntity(Entity* entity)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    if (const size_t num = s_Instance->m_Entities.erase(entity); num == 0) return false;

    std::erase(s_Instance->m_OnStartQueue, entity);
    std::erase(s_Instance->m_OnUpdateQueue, entity);

    return true;
}

void EntityManager::AddComponent(Component* component)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    s_Instance->m_Components.insert(component);

    AddToQueue(component, s_Instance->m_OnStartQueue);
    AddToQueue(component, s_Instance->m_OnUpdateQueue);

    if (const auto renderable = dynamic_cast<Renderable*>(component))
    {
        s_Instance->m_RenderQueue.push_back(renderable);
    }
}

bool EntityManager::RemoveComponent(Component* component)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    if (const size_t num = s_Instance->m_Components.erase(component); num == 0) return false;

    std::erase(s_Instance->m_OnStartQueue, component);
    std::erase(s_Instance->m_OnUpdateQueue, component);

    if (const auto renderable = dynamic_cast<Renderable*>(component))
    {
        std::erase(s_Instance->m_RenderQueue, renderable);
    }

    return true;
}

GameMode* EntityManager::GetGameMode()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_GameMode;
}

std::unordered_set<Entity*>& EntityManager::GetEntities()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_Entities;
}

std::unordered_set<Component*>& EntityManager::GetComponents()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_Components;
}

void EntityManager::AddToQueue(Updatable* updatable, std::vector<Updatable*>& queue)
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
