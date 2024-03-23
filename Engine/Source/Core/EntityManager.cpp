#include "EntityManager.h"

#include "Components/TextureRenderer.h"
#include "Game/GameMode.h"
#include "Game/Entity.h"
#include "Game/Component.h"
#include "Game/Base/Updatable.h"
#include "Util/Macros/SingletonMacros.hpp"

#ifdef DEBUG
#include "Game/ImGui/ImGuiRenderer.h"
#include "Game/ImGui/ImGuiMenuRender.h"
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

void EntityManager::Terminate() const
{
    while (!m_Entities.empty())
    {
        DestroyEntity(m_Entities.begin()->second);
    }

    DestroyGameMode();
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
    // Render queue

    for (const auto& renderable : m_RenderQueue)
    {
        renderable->Render();
    }

    // ImGui windows / menus

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

GameMode* EntityManager::GetGameMode()
{
    ASSERT_SINGLETON_INITIALIZED();

    return s_Instance->m_GameMode;
}

Entity* EntityManager::GetEntity(const uint64_t id)
{
    ASSERT_SINGLETON_INITIALIZED();

    const auto it = s_Instance->m_Entities.find(id);
    if (it != s_Instance->m_Entities.end()) return it->second;
    return nullptr;
}

Component* EntityManager::GetComponent(const uint64_t id)
{
    ASSERT_SINGLETON_INITIALIZED();

    const auto it = s_Instance->m_Components.find(id);
    if (it != s_Instance->m_Components.end()) return it->second;
    return nullptr;
}

size_t EntityManager::GetEntityCount()
{
    ASSERT_SINGLETON_INITIALIZED();

    return s_Instance->m_Entities.size();
}

size_t EntityManager::GetComponentCount()
{
    ASSERT_SINGLETON_INITIALIZED();

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

void EntityManager::AddToImGuiQueue(ImGuiMenuRenderer* renderer, std::vector<ImGuiMenuRenderer*>& queue)
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
        m_RenderQueue.push_back(renderable);
    }

    // ImGui Renderer

#ifdef DEBUG
    if (const auto imguiRenderer = dynamic_cast<ImGuiRenderer*>(object); imguiRenderer != nullptr)
    {
        m_ImGuiRenderQueue.push_back(imguiRenderer);
    }

    if (const auto imguiMenuRenderer = dynamic_cast<ImGuiMenuRenderer*>(object); imguiMenuRenderer != nullptr)
    {
        AddToImGuiQueue(imguiMenuRenderer, m_ImGuiMenuRenderQueue);
    }
#endif
}

void EntityManager::RemoveObjectCallbacks(Object* object)
{
    // Renderable

    if (const auto renderable = dynamic_cast<Renderable*>(object); renderable != nullptr)
    {
        std::erase(m_RenderQueue, renderable);
    }

    // ImGui Renderer

#ifdef DEBUG
    if (const auto imguiRenderer = dynamic_cast<ImGuiRenderer*>(object); imguiRenderer != nullptr)
    {
        std::erase(m_ImGuiRenderQueue, imguiRenderer);
    }

    if (const auto imguiMenuRenderer = dynamic_cast<ImGuiMenuRenderer*>(object); imguiMenuRenderer != nullptr)
    {
        std::erase(m_ImGuiMenuRenderQueue, imguiMenuRenderer);
    }
#endif
}

void EntityManager::SetupEntityComponentRelationship(Entity* entity, Component* component)
{
    entity->m_Components.push_back(component);
    component->m_Parent = entity;
}

void EntityManager::DestroyGameMode()
{
    ASSERT_SINGLETON_INITIALIZED();

    if (s_Instance->m_GameMode == nullptr) return;

    s_Instance->RemoveObjectCallbacks(s_Instance->m_GameMode);

    PREPARE_SPAWNER_USAGE(GameMode);

    delete s_Instance->m_GameMode;

    s_Instance->m_GameMode = nullptr;
}

void EntityManager::DestroyEntity(Entity* entity)
{
    ASSERT_SINGLETON_INITIALIZED();

    if (const size_t num = s_Instance->m_Entities.erase(entity->m_Id); num == 0) return;

    std::erase(s_Instance->m_OnStartQueue, entity);
    std::erase(s_Instance->m_OnUpdateQueue, entity);

    s_Instance->RemoveObjectCallbacks(entity);

    entity->DetachAllComponents();

    PREPARE_SPAWNER_USAGE(Entity);

    delete entity;
}

void EntityManager::DestroyComponent(Component* component)
{
    ASSERT_SINGLETON_INITIALIZED();

    if (const size_t num = s_Instance->m_Components.erase(component->m_Id); num == 0) return;

    std::erase(s_Instance->m_OnStartQueue, component);
    std::erase(s_Instance->m_OnUpdateQueue, component);

    s_Instance->RemoveObjectCallbacks(component);

    std::erase(component->m_Parent->m_Components, component);

    PREPARE_SPAWNER_USAGE(Component);

    delete component;
}
