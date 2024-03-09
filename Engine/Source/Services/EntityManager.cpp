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
    DestroyGameMode();

    while (!m_Entities.empty())
    {
        DestroyEntity(*m_Entities.begin());
    }

    s_Instance = nullptr;
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

Engine::Game::GameMode* EntityManager::GetGameMode()
{
    SINGLETON_CHECK_IF_INITIALIZED("EntityManager");

    return s_Instance->m_GameMode;
}

void EntityManager::DestroyGameMode()
{
    SINGLETON_CHECK_IF_INITIALIZED("EntityManager");

    PREPARE_SINGLETON_USAGE();

    delete s_Instance->m_GameMode;
    s_Instance->m_GameMode = nullptr;
}

void EntityManager::DestroyEntity(Game::Entity* entity)
{
    SINGLETON_CHECK_IF_INITIALIZED("EntityManager");

    if (const size_t num = s_Instance->m_Entities.erase(entity); num == 0) return;

    std::erase(s_Instance->m_OnStartQueue, entity);
    std::erase(s_Instance->m_OnUpdateQueue, entity);

    while (!entity->m_Components.empty())
    {
        DetachComponent(entity->m_Components.front());
    }

    PREPARE_SINGLETON_USAGE();

    delete entity;
}

void EntityManager::DetachComponent(Game::Component* component)
{
    SINGLETON_CHECK_IF_INITIALIZED("EntityManager");

    if (const size_t num = s_Instance->m_Components.erase(component); num == 0) return;

    std::erase(s_Instance->m_OnStartQueue, component);
    std::erase(s_Instance->m_OnUpdateQueue, component);

    auto& parentComponents = component->m_Parent->m_Components;
    std::erase(parentComponents, component);

    if (const auto renderable = dynamic_cast<Game::Internal::Renderable*>(component))
    {
        std::erase(s_Instance->m_RenderQueue, renderable);
    }

    PREPARE_SINGLETON_USAGE();

    delete component;
}
