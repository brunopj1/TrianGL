#include "EntityManager.h"

#include "Components/TextureRenderer.h"
#include "Game/GameMode.h"
#include "Game/Entity.h"
#include "Game/Component.h"
#include "Game/Base/Updatable.h"
#include "Util/Macros/SingletonMacros.hpp"
#include "Game/ImGui/ImGuiRenderer.h"
#include "Game/ImGui/ImGuiMenuRender.h"

#ifdef DEBUG
#include <imgui.h>
#endif

using namespace TGL;

EntityManager::EntityManager()
{
    s_Instance = this;
}

EntityManager::~EntityManager()
{
    // The objects are destroyed in the Terminate method
    // to prevent destroying them after the OpenGL context is destroyed

    s_Instance = nullptr;
}

void EntityManager::Terminate()
{
    m_GameMode->Destroy();

    while (!m_Entities.empty())
    {
        const auto [_, entity] = *m_Entities.begin();
        entity->Destroy();
    }
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
    ASSERT_SINGLETON_INITIALIZED(TGL::EntityManager);

    s_Instance->m_GameMode = gameMode;

    if (gameMode != nullptr)
    {
        gameMode->m_Id = s_Instance->m_NextId++;

        StoreObjectCallbacks(gameMode);
    }
    else
    {
        RemoveObjectCallbacks(s_Instance->m_GameMode);
    }
}

void EntityManager::AddEntity(Entity* entity)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::EntityManager);

    entity->m_Id = s_Instance->m_NextId++;

    s_Instance->m_Entities.emplace(entity->m_Id, entity);

    AddToQueue(entity, s_Instance->m_OnStartQueue);
    AddToQueue(entity, s_Instance->m_OnUpdateQueue);

    StoreObjectCallbacks(entity);
}

Entity* EntityManager::GetEntity(const uint64_t id)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::EntityManager);

    const auto it = s_Instance->m_Entities.find(id);
    if (it != s_Instance->m_Entities.end()) return it->second;
    return nullptr;
}

bool EntityManager::RemoveEntity(Entity* entity)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::EntityManager);

    if (const size_t num = s_Instance->m_Entities.erase(entity->m_Id); num == 0) return false;

    std::erase(s_Instance->m_OnStartQueue, entity);
    std::erase(s_Instance->m_OnUpdateQueue, entity);

    RemoveObjectCallbacks(entity);

    return true;
}

void EntityManager::AddComponent(Component* component)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::EntityManager);

    component->m_Id = s_Instance->m_NextId++;

    s_Instance->m_Components.emplace(component->m_Id, component);

    AddToQueue(component, s_Instance->m_OnStartQueue);
    AddToQueue(component, s_Instance->m_OnUpdateQueue);

    StoreObjectCallbacks(component);
}

Component* EntityManager::GetComponent(const uint64_t id)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::EntityManager);

    const auto it = s_Instance->m_Components.find(id);
    if (it != s_Instance->m_Components.end()) return it->second;
    return nullptr;
}

bool EntityManager::RemoveComponent(Component* component)
{
    ASSERT_SINGLETON_INITIALIZED(TGL::EntityManager);

    if (const size_t num = s_Instance->m_Components.erase(component->m_Id); num == 0) return false;

    std::erase(s_Instance->m_OnStartQueue, component);
    std::erase(s_Instance->m_OnUpdateQueue, component);

    RemoveObjectCallbacks(component);

    return true;
}

GameMode* EntityManager::GetGameMode()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::EntityManager);

    return s_Instance->m_GameMode;
}

std::unordered_map<uint64_t, Entity*>& EntityManager::GetEntities()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::EntityManager);

    return s_Instance->m_Entities;
}

std::unordered_map<uint64_t, Component*>& EntityManager::GetComponents()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::EntityManager);

    return s_Instance->m_Components;
}

size_t EntityManager::GetEntityCount()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::EntityManager);

    return s_Instance->m_Entities.size();
}

size_t EntityManager::GetComponentCount()
{
    ASSERT_SINGLETON_INITIALIZED(TGL::EntityManager);

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

void EntityManager::StoreObjectCallbacks(Object* object)
{
    // Renderable

    if (const auto renderable = dynamic_cast<Renderable*>(object); renderable != nullptr)
    {
        s_Instance->m_RenderQueue.push_back(renderable);
    }

    // ImGui Renderer

#ifdef DEBUG
    if (const auto imguiRenderer = dynamic_cast<ImGuiRenderer*>(object); imguiRenderer != nullptr)
    {
        s_Instance->m_ImGuiRenderQueue.push_back(imguiRenderer);
    }

    if (const auto imguiMenuRenderer = dynamic_cast<ImGuiMenuRenderer*>(object); imguiMenuRenderer != nullptr)
    {
        AddToRenderQueue(imguiMenuRenderer, s_Instance->m_ImGuiMenuRenderQueue);
    }
#endif
}

void EntityManager::RemoveObjectCallbacks(Object* object)
{
    // Renderable

    if (const auto renderable = dynamic_cast<Renderable*>(object); renderable != nullptr)
    {
        std::erase(s_Instance->m_RenderQueue, renderable);
    }

    // ImGui Renderer

#ifdef DEBUG
    if (const auto imguiRenderer = dynamic_cast<ImGuiRenderer*>(object); imguiRenderer != nullptr)
    {
        std::erase(s_Instance->m_ImGuiRenderQueue, imguiRenderer);
    }

    if (const auto imguiMenuRenderer = dynamic_cast<ImGuiMenuRenderer*>(object); imguiMenuRenderer != nullptr)
    {
        std::erase(s_Instance->m_ImGuiMenuRenderQueue, imguiMenuRenderer);
    }
#endif
}
