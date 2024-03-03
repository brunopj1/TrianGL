#include "EntityManager.h"

#include "Game/GameMode.h"
#include "Game/IUpdatable.h"
#include "Game/Entity.h"
#include "Game/Component.h"

using namespace Engine::Core;

EntityManager::EntityManager()
{
    s_Instance = this;
}

EntityManager::~EntityManager()
{
    DestroyGameMode();

    for (const Game::Entity* entity : m_Entities)
    {
        delete entity;
    }

    for (const Game::Component* component : m_Components)
    {
        delete component;
    }

    m_Entities.clear();
    m_Components.clear();

    m_OnStartQueue.clear();
    m_OnUpdateQueue.clear();
}

EntityManager* EntityManager::GetInstance()
{
    return s_Instance;
}

void EntityManager::Update()
{
    for (Game::IUpdatable* updatable : m_OnStartQueue)
    {
        updatable->OnStart();
    }
    m_OnStartQueue.clear();

    m_GameMode->OnEarlyUpdate();

    for (Game::IUpdatable* updatable : m_OnUpdateQueue)
    {
        if (updatable->m_ShouldUpdate)
        {
            updatable->OnUpdate();
        }
    }

    m_GameMode->OnLateUpdate();
}

void EntityManager::Render() const
{}

void EntityManager::AddToQueue(Game::IUpdatable* updatable, std::vector<Game::IUpdatable*>& queue)
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

Engine::Game::GameMode* EntityManager::GetGameMode() const
{
    return m_GameMode;
}

void EntityManager::DestroyGameMode()
{
    delete m_GameMode;
    m_GameMode = nullptr;
}

void EntityManager::DestroyEntity(Game::Entity* entity)
{
    // Remove from the EntityManager

    m_Entities.erase(entity);

    m_OnStartQueue.erase(std::remove(m_OnStartQueue.begin(), m_OnStartQueue.end(), entity), m_OnStartQueue.end());

    m_OnUpdateQueue.erase(std::remove(m_OnUpdateQueue.begin(), m_OnUpdateQueue.end(), entity), m_OnUpdateQueue.end());

    // Detach all components

    while (!entity->m_Components.empty())
    {
        DetachComponent(entity->m_Components.front());
    }

    // Delete the entity

    delete entity;
}

void EntityManager::DetachComponent(Game::Component* component)
{
    // Remove from the EntityManager

    m_Components.erase(component);

    m_OnStartQueue.erase(std::remove(m_OnStartQueue.begin(), m_OnStartQueue.end(), component), m_OnStartQueue.end());

    m_OnUpdateQueue.erase(std::remove(m_OnUpdateQueue.begin(), m_OnUpdateQueue.end(), component), m_OnUpdateQueue.end());

    // Remove from the parent Entity

    auto& parentComponents = component->m_Parent->m_Components;
    parentComponents.erase(std::remove(parentComponents.begin(), parentComponents.end(), component), parentComponents.end());

    // Delete the component

    delete component;
}
