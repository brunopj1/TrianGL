#include <Core/Services/Private/EntityManager.h>
#include <Game/Component.h>
#include <Game/Entity.h>
#include <Game/GameMode.h>
#include <Rendering/SpriteRenderer.h>

using namespace TGL;

// NOLINTBEGIN(CppMemberFunctionMayBeStatic)

void EntityManager::Init()
{}

void EntityManager::Terminate()
{
	while (!m_Entities.empty())
	{
		DestroyEntity(m_Entities.begin()->second);
	}

	DestroyGameMode();
}

u64 EntityManager::GetNextId()
{
	return m_NextId++;
}

void EntityManager::Update(const f32 deltaTime)
{
	if (!m_OnStartQueue.empty())
	{
		// Copy the queue to avoid issues when instantiating new objects in OnStart methods

		const auto queue = m_OnStartQueue;

		m_OnStartQueue.clear();

		for (GameObject* object : queue)
		{
			object->OnStart();

			if (object->m_ShouldUpdate)
			{
				AddToUpdateQueue(object, m_OnUpdateQueue);
			}
		}
	}

	m_GameMode->OnEarlyUpdate(deltaTime);

	for (GameObject* object : m_OnUpdateQueue)
	{
		object->OnUpdate(deltaTime);
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

GameMode* EntityManager::GetGameMode() const
{
	return m_GameMode;
}

Entity* EntityManager::GetEntity(const u64 id) const
{
	const auto it = m_Entities.find(id);
	if (it != m_Entities.end())
	{
		return it->second;
	}
	return nullptr;
}

Component* EntityManager::GetComponent(const u64 id) const
{
	const auto it = m_Components.find(id);
	if (it != m_Components.end())
	{
		return it->second;
	}
	return nullptr;
}

u32 EntityManager::GetEntityCount() const
{
	return static_cast<u32>(m_Entities.size());
}

u32 EntityManager::GetComponentCount() const
{
	return static_cast<u32>(m_Components.size());
}

void EntityManager::RemoveObjectCallbacks(GameObject* object)
{
	// Updatable

	std::erase(m_OnStartQueue, object);
	std::erase(m_OnUpdateQueue, object);

	// Renderable

	if (const auto renderable = dynamic_cast<Renderable*>(object); renderable != nullptr)
	{
		std::erase(m_RenderQueue, renderable);
	}
}

void EntityManager::AddToUpdateQueue(GameObject* object, std::vector<GameObject*>& queue)
{
	const auto order = object->m_OrderOfExecution;

	for (auto it = queue.begin(); it != queue.end(); ++it)
	{
		if ((*it)->m_OrderOfExecution > order)
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

void EntityManager::UpdateRenderableOrder(Renderable* renderable)
{
	std::erase(m_RenderQueue, renderable);

	AddToRenderQueue(renderable, m_RenderQueue);
}

void EntityManager::SetupEntityComponentRelationship(Entity* entity, Component* component)
{
	entity->m_Components.push_back(component);
	component->m_Parent = entity;
}

void EntityManager::DestroyGameMode()
{
	if (m_GameMode == nullptr)
	{
		return;
	}

	RemoveObjectCallbacks(m_GameMode);

	PREPARE_ENTITY_FACTORY_DESTRUCTOR(GameMode);

	delete m_GameMode;
	m_GameMode = nullptr;

	ASSERT_POST_ENTITY_FACTORY_DESTRUCTOR(GameMode);
}

void EntityManager::DestroyEntity(Entity* entity)
{
	if (const size_t num = m_Entities.erase(entity->m_Id); num == 0)
	{
		return;
	}

	RemoveObjectCallbacks(entity);

	entity->DetachAllComponents();

	PREPARE_ENTITY_FACTORY_DESTRUCTOR(Entity);

	delete entity;

	ASSERT_POST_ENTITY_FACTORY_DESTRUCTOR(Entity);
}

void EntityManager::DestroyComponent(Component* component)
{
	if (const size_t num = m_Components.erase(component->m_Id); num == 0)
	{
		return;
	}

	RemoveObjectCallbacks(component);

	std::erase(component->m_Parent->m_Components, component);

	PREPARE_ENTITY_FACTORY_DESTRUCTOR(Component);

	delete component;

	ASSERT_POST_ENTITY_FACTORY_DESTRUCTOR(Component);
}

// NOLINTEND(CppMemberFunctionMayBeStatic)
