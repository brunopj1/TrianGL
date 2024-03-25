#include "EntityManager.h"

#include "Implementations/Components/SpriteRenderer.h"
#include "Game/GameMode.h"
#include "Game/Entity.h"
#include "Game/Component.h"
#include "Util/Macros/SingletonMacros.h"

#ifdef DEBUG
#include "Rendering/ImGui/ImGuiRenderer.h"
#include "Rendering/ImGui/ImGuiMenuRender.h"
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
    for (Object* object : m_OnStartQueue)
    {
        object->OnStart();
    }
    m_OnStartQueue.clear();

    m_GameMode->OnEarlyUpdate(deltaTime);

    for (Object* object : m_OnUpdateQueue)
    {
        if (object->m_ShouldUpdate)
        {
            object->OnUpdate(deltaTime);
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

void EntityManager::AddToUpdateQueue(Object* object, std::vector<Object*>& queue)
{
    const auto order = object->GetOrderOfExecution();

    for (auto it = queue.begin(); it != queue.end(); ++it)
    {
        if ((*it)->GetOrderOfExecution() > order)
        {
            queue.insert(it, object);
            return;
        }
    }

    queue.push_back(object);
}

void EntityManager::AddToRenderQueue(Renderable* renderable, std::vector<Renderable*>& queue)
{
    const auto order = renderable->GetZIndex();

    for (auto it = queue.begin(); it != queue.end(); ++it)
    {
        if ((*it)->GetZIndex() > order)
        {
            queue.insert(it, renderable);
            return;
        }
    }

    queue.push_back(renderable);
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
    // Updatable

    AddToUpdateQueue(object, m_OnStartQueue);
    AddToUpdateQueue(object, m_OnUpdateQueue);

    // Renderable

    if (const auto renderable = dynamic_cast<Renderable*>(object); renderable != nullptr)
    {
        AddToRenderQueue(renderable, m_RenderQueue);
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
    // Updatable

    std::erase(m_OnStartQueue, object);
    std::erase(m_OnUpdateQueue, object);

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

void EntityManager::UpdateRenderableOrder(Renderable* renderable)
{
    ASSERT_SINGLETON_INITIALIZED();

    std::erase(s_Instance->m_RenderQueue, renderable);

    AddToRenderQueue(renderable, s_Instance->m_RenderQueue);
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

    s_Instance->RemoveObjectCallbacks(entity);

    entity->DetachAllComponents();

    PREPARE_SPAWNER_USAGE(Entity);

    delete entity;
}

void EntityManager::DestroyComponent(Component* component)
{
    ASSERT_SINGLETON_INITIALIZED();

    if (const size_t num = s_Instance->m_Components.erase(component->m_Id); num == 0) return;

    s_Instance->RemoveObjectCallbacks(component);

    std::erase(component->m_Parent->m_Components, component);

    PREPARE_SPAWNER_USAGE(Component);

    delete component;
}
