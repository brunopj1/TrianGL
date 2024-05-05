#include "EntityManager.h"

#include "Implementations/Components/SpriteRenderer.h"
#include "Game/GameMode.h"
#include "Game/Entity.h"
#include "Game/Component.h"
#include "Util/Macros/SingletonMacros.h"

using namespace TGL;

void EntityManager::Init()
{
    s_CanCreateAndDestroyObjects = true;
}

void EntityManager::Terminate()
{
    s_CanCreateAndDestroyObjects = false;

    while (!s_Entities.empty())
    {
        DestroyEntity(s_Entities.begin()->second);
    }

    DestroyGameMode();
}

void EntityManager::Update(const float deltaTime)
{
    for (GameObject* object : s_OnStartQueue)
    {
        object->OnStart();

        if (object->m_ShouldUpdate)
        {
            AddToUpdateQueue(object, s_OnUpdateQueue);
        }
    }

    s_OnStartQueue.clear();

    s_GameMode->OnEarlyUpdate(deltaTime);

    for (GameObject* object : s_OnUpdateQueue)
    {
        object->OnUpdate(deltaTime);
    }

    s_GameMode->OnLateUpdate(deltaTime);
}

void EntityManager::Render()
{
    for (const auto& renderable : s_RenderQueue)
    {
        renderable->Render();
    }
}

GameMode* EntityManager::GetGameMode()
{
    return s_GameMode;
}

Entity* EntityManager::GetEntity(const uint64_t id)
{
    const auto it = s_Entities.find(id);
    if (it != s_Entities.end()) return it->second;
    return nullptr;
}

Component* EntityManager::GetComponent(const uint64_t id)
{
    const auto it = s_Components.find(id);
    if (it != s_Components.end()) return it->second;
    return nullptr;
}

size_t EntityManager::GetEntityCount()
{
    return s_Entities.size();
}

size_t EntityManager::GetComponentCount()
{
    return s_Components.size();
}

void EntityManager::AddToUpdateQueue(GameObject* object, std::vector<GameObject*>& queue)
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

void EntityManager::StoreObjectCallbacks(GameObject* object)
{
    // Updatable

    AddToUpdateQueue(object, s_OnStartQueue);
    // The object will be added to the update queue when it leaves the start queue

    // Renderable

    if (const auto renderable = dynamic_cast<Renderable*>(object); renderable != nullptr)
    {
        AddToRenderQueue(renderable, s_RenderQueue);
    }
}

void EntityManager::RemoveObjectCallbacks(GameObject* object)
{
    // Updatable

    std::erase(s_OnStartQueue, object);
    std::erase(s_OnUpdateQueue, object);

    // Renderable

    if (const auto renderable = dynamic_cast<Renderable*>(object); renderable != nullptr)
    {
        std::erase(s_RenderQueue, renderable);
    }
}

void EntityManager::UpdateRenderableOrder(Renderable* renderable)
{
    std::erase(s_RenderQueue, renderable);

    AddToRenderQueue(renderable, s_RenderQueue);
}

void EntityManager::SetupEntityComponentRelationship(Entity* entity, Component* component)
{
    entity->m_Components.push_back(component);
    component->m_Parent = entity;
}

void EntityManager::DestroyGameMode()
{
    if (s_GameMode == nullptr) return;

    RemoveObjectCallbacks(s_GameMode);

    PREPARE_SPAWNER_USAGE(GameMode);

    delete s_GameMode;

    s_GameMode = nullptr;
}

void EntityManager::DestroyEntity(Entity* entity)
{
    if (const size_t num = s_Entities.erase(entity->m_Id); num == 0) return;

    RemoveObjectCallbacks(entity);

    entity->DetachAllComponents();

    PREPARE_SPAWNER_USAGE(Entity);

    delete entity;
}

void EntityManager::DestroyComponent(Component* component)
{
    if (const size_t num = s_Components.erase(component->m_Id); num == 0) return;

    RemoveObjectCallbacks(component);

    std::erase(component->m_Parent->m_Components, component);

    PREPARE_SPAWNER_USAGE(Component);

    delete component;
}
