#include "EntityManager.h"

#include "IdGenerator.h"
#include "Components/TextureRenderer.h"
#include "Game/GameMode.h"
#include "Game/Entity.h"
#include "Game/Component.h"
#include "Game/Base/ImGuiMenuRender.h"
#include "Game/Base/Updatable.h"
#include "Util/Macros/SingletonMacros.hpp"

#ifdef DEBUG
#include "Game/Base/ImGuiRenderer.h"
#include <imgui.h>
#endif

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

#ifdef DEBUG
    if (!m_ImGuiMenuRenderQueue.empty())
    {
        ImGui::BeginMainMenuBar();

        for (const auto& renderable : m_ImGuiMenuRenderQueue)
        {
            renderable->RenderImGuiMenu();
        }

        ImGui::EndMainMenuBar();
    }

    for (const auto& renderable : m_ImGuiRenderQueue)
    {
        renderable->RenderImGui();
    }
#endif
}

void EntityManager::SetGameMode(GameMode* gameMode)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    s_Instance->m_GameMode = gameMode;

#ifdef DEBUG

    if (gameMode != nullptr)
    {
        if (const auto imguiRenderer = dynamic_cast<ImGuiRenderer*>(gameMode); imguiRenderer != nullptr)
        {
            s_Instance->m_ImGuiRenderQueue.push_back(imguiRenderer);
        }

        if (const auto imguiMenuRenderer = dynamic_cast<ImGuiMenuRenderer*>(gameMode); imguiMenuRenderer != nullptr)
        {
            s_Instance->m_ImGuiMenuRenderQueue.push_back(imguiMenuRenderer);
        }
    }
    else
    {
        if (const auto imguiRenderer = dynamic_cast<ImGuiRenderer*>(gameMode); imguiRenderer != nullptr)
        {
            std::erase(s_Instance->m_ImGuiRenderQueue, imguiRenderer);
        }

        if (const auto imguiMenuRenderer = dynamic_cast<ImGuiMenuRenderer*>(gameMode); imguiMenuRenderer != nullptr)
        {
            std::erase(s_Instance->m_ImGuiMenuRenderQueue, imguiMenuRenderer);
        }
    }

#endif
}

void EntityManager::AddEntity(Entity* entity)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    entity->m_Id = s_Instance->m_IdGenerator->NextId();

    s_Instance->m_Entities.emplace(entity->m_Id, entity);

    AddToQueue(entity, s_Instance->m_OnStartQueue);
    AddToQueue(entity, s_Instance->m_OnUpdateQueue);

#ifdef DEBUG
    if (const auto imguiRenderer = dynamic_cast<ImGuiRenderer*>(entity); imguiRenderer != nullptr)
    {
        s_Instance->m_ImGuiRenderQueue.push_back(imguiRenderer);
    }

    if (const auto imguiMenuRenderer = dynamic_cast<ImGuiMenuRenderer*>(entity); imguiMenuRenderer != nullptr)
    {
        AddToRenderQueue(imguiMenuRenderer, s_Instance->m_ImGuiMenuRenderQueue);
    }
#endif
}

Entity* EntityManager::GetEntity(const uint64_t id)
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

#ifdef DEBUG
    if (const auto imguiRenderer = dynamic_cast<ImGuiRenderer*>(entity); imguiRenderer != nullptr)
    {
        std::erase(s_Instance->m_ImGuiRenderQueue, imguiRenderer);
    }

    if (const auto imguiMenuRenderer = dynamic_cast<ImGuiMenuRenderer*>(entity); imguiMenuRenderer != nullptr)
    {
        std::erase(s_Instance->m_ImGuiMenuRenderQueue, imguiMenuRenderer);
    }
#endif

    return true;
}

void EntityManager::AddComponent(Component* component)
{
    SINGLETON_CHECK_IF_INITIALIZED();

    component->m_Id = s_Instance->m_IdGenerator->NextId();

    s_Instance->m_Components.emplace(component->m_Id, component);

    AddToQueue(component, s_Instance->m_OnStartQueue);
    AddToQueue(component, s_Instance->m_OnUpdateQueue);

    if (const auto renderable = dynamic_cast<Renderable*>(component); renderable != nullptr)
    {
        s_Instance->m_RenderQueue.push_back(renderable);
    }

#ifdef DEBUG
    if (const auto imguiRenderer = dynamic_cast<ImGuiRenderer*>(component); imguiRenderer != nullptr)
    {
        s_Instance->m_ImGuiRenderQueue.push_back(imguiRenderer);
    }

    if (const auto imguiMenuRenderer = dynamic_cast<ImGuiMenuRenderer*>(component); imguiMenuRenderer != nullptr)
    {
        AddToRenderQueue(imguiMenuRenderer, s_Instance->m_ImGuiMenuRenderQueue);
    }
#endif
}

Component* EntityManager::GetComponent(const uint64_t id)
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

    if (const auto renderable = dynamic_cast<Renderable*>(component); renderable != nullptr)
    {
        std::erase(s_Instance->m_RenderQueue, renderable);
    }

#ifdef DEBUG
    if (const auto imguiRenderer = dynamic_cast<ImGuiRenderer*>(component); imguiRenderer != nullptr)
    {
        std::erase(s_Instance->m_ImGuiRenderQueue, imguiRenderer);
    }

    if (const auto imguiMenuRenderer = dynamic_cast<ImGuiMenuRenderer*>(component); imguiMenuRenderer != nullptr)
    {
        s_Instance->m_ImGuiMenuRenderQueue.push_back(imguiMenuRenderer);
    }
#endif

    return true;
}

GameMode* EntityManager::GetGameMode()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_GameMode;
}

std::unordered_map<uint64_t, Entity*>& EntityManager::GetEntities()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_Entities;
}

std::unordered_map<uint64_t, Component*>& EntityManager::GetComponents()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_Components;
}

size_t EntityManager::GetEntityCount()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_Entities.size();
}

size_t EntityManager::GetComponentCount()
{
    SINGLETON_CHECK_IF_INITIALIZED();

    return s_Instance->m_Components.size();
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

#if DEBUG

void EntityManager::AddToRenderQueue(ImGuiMenuRenderer* renderer, std::vector<ImGuiMenuRenderer*>& queue)
{
    const auto order = renderer->GetRenderOrder();

    for (auto it = queue.begin(); it != queue.end(); ++it)
    {
        if ((*it)->GetRenderOrder() > order)
        {
            queue.insert(it, renderer);
            return;
        }
    }

    queue.push_back(renderer);
}

#endif
