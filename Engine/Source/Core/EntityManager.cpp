#include "EntityManager.h"

#include "IdGenerator.h"
#include "Components/TextureRenderer.h"
#include "Game/GameMode.h"
#include "Game/Entity.h"
#include "Game/Component.h"
#include "Game/Base/Updatable.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace TGL;

EntityManager::EntityManager(IdGenerator* idGenerator)
    : m_IdGenerator(idGenerator)
{
    s_Instance = this;
}

EntityManager::~EntityManager()
{
    m_GameMode->Destroy();

    while (!m_Entities.empty())
    {
        const auto [_, entity] = *m_Entities.begin();
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
    for (const auto& renderable : m_RenderQueue)
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

    entity->m_Id = s_Instance->m_IdGenerator->NextId();

    s_Instance->m_Entities.emplace(entity->m_Id, entity);

    AddToQueue(entity, s_Instance->m_OnStartQueue);
    AddToQueue(entity, s_Instance->m_OnUpdateQueue);
}

Entity* EntityManager::GetEntity(const uint32_t id)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    const auto it = s_Instance->m_Entities.find(id);
    if (it != s_Instance->m_Entities.end()) return it->second;
    return nullptr;
}

bool EntityManager::RemoveEntity(Entity* entity)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    if (const size_t num = s_Instance->m_Entities.erase(entity->m_Id); num == 0) return false;

    std::erase(s_Instance->m_OnStartQueue, entity);
    std::erase(s_Instance->m_OnUpdateQueue, entity);

    return true;
}

void EntityManager::AddComponent(Component* component)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    component->m_Id = s_Instance->m_IdGenerator->NextId();

    s_Instance->m_Components.emplace(component->m_Id, component);

    AddToQueue(component, s_Instance->m_OnStartQueue);
    AddToQueue(component, s_Instance->m_OnUpdateQueue);

    if (const auto renderable = dynamic_cast<Renderable*>(component))
    {
        s_Instance->m_RenderQueue.push_back(renderable);
    }
}

Component* EntityManager::GetComponent(const uint32_t id)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    const auto it = s_Instance->m_Components.find(id);
    if (it != s_Instance->m_Components.end()) return it->second;
    return nullptr;
}

bool EntityManager::RemoveComponent(Component* component)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    if (const size_t num = s_Instance->m_Components.erase(component->m_Id); num == 0) return false;

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

std::unordered_map<uint32_t, Entity*>& EntityManager::GetEntities()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_Entities;
}

std::unordered_map<uint32_t, Component*>& EntityManager::GetComponents()
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
