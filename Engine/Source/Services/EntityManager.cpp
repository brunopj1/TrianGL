#include "EntityManager.h"

#include "Components/TextureRenderer.h"
#include "Game/GameMode.h"
#include "Game/Entity.h"
#include "Game/Component.h"
#include "Game/Internal/IUpdatable.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Services;

EntityManager::EntityManager()
{
    s_Instance = this;
}

EntityManager::~EntityManager()
{
    PREPARE_SINGLETON_USAGE(true);

    delete s_Instance->m_GameMode;

    for (const Game::Entity* entity : m_Entities)
    {
        delete entity;
    }

    for (const Game::Component* component : m_Components)
    {
        delete component;
    }

    s_Instance = nullptr;

    PREPARE_SINGLETON_USAGE(false);
}

void EntityManager::InitializeComponents()
{
    Components::TextureRenderer::Init();
}

void EntityManager::TerminateComponents()
{
    Components::TextureRenderer::Terminate();
}

void EntityManager::Update(const float deltaTime)
{
    for (Game::Internal::IUpdatable* updatable : m_OnStartQueue)
    {
        updatable->OnStart();
    }
    m_OnStartQueue.clear();

    m_GameMode->OnEarlyUpdate(deltaTime);

    for (Game::Internal::IUpdatable* updatable : m_OnUpdateQueue)
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
    for (const Game::Internal::IRenderable* renderable : m_RenderQueue)
    {
        renderable->Render();
    }
}

void EntityManager::AddToQueue(Game::Internal::IUpdatable* updatable, std::vector<Game::Internal::IUpdatable*>& queue)
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

Engine::Game::GameMode* EntityManager::GetGameMode()
{
    DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

    return s_Instance->m_GameMode;
}

void EntityManager::DestroyGameMode()
{
    DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

    PREPARE_SINGLETON_USAGE(true);

    delete s_Instance->m_GameMode;
    s_Instance->m_GameMode = nullptr;

    PREPARE_SINGLETON_USAGE(false);
}

void EntityManager::DestroyEntity(Game::Entity* entity)
{
    DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

    PREPARE_SINGLETON_USAGE(true);

    s_Instance->m_Entities.erase(entity);

    std::erase(s_Instance->m_OnStartQueue, entity);
    std::erase(s_Instance->m_OnUpdateQueue, entity);

    while (!entity->m_Components.empty())
    {
        DetachComponent(entity->m_Components.front());
    }

    delete entity;

    PREPARE_SINGLETON_USAGE(false);
}

void EntityManager::DetachComponent(Game::Component* component)
{
    DEBUG_SINGLETON_INSTANCE(s_Instance, "EntityManager");

    PREPARE_SINGLETON_USAGE(true);

    s_Instance->m_Components.erase(component);

    std::erase(s_Instance->m_OnStartQueue, component);
    std::erase(s_Instance->m_OnUpdateQueue, component);

    auto& parentComponents = component->m_Parent->m_Components;
    std::erase(parentComponents, component);

    if (const auto renderable = dynamic_cast<Game::Internal::IRenderable*>(component))
    {
        std::erase(s_Instance->m_RenderQueue, renderable);
    }

    delete component;

    PREPARE_SINGLETON_USAGE(false);
}
