#include <Core/Services/Private/EntityManager.h>
#include <Game/GameMode.h>

using namespace TGL;

GameMode::GameMode(const i32 orderOfExecution)
	: GameObject(true, orderOfExecution)
{
	ASSERT_ENTITY_FACTORY_CONSTRUCTOR(GameMode);

	EntityManager& entityManager = EntityManager::Get();
	entityManager.m_GameMode = this;
}

GameMode::~GameMode()
{
	ASSERT_ENTITY_FACTORY_DESTRUCTOR(GameMode);

	// EntityManager::m_GameMode is updated after the virtual destructor completes
}

void GameMode::OnEarlyUpdate(f32 deltaTime) {}

void GameMode::OnLateUpdate(f32 deltaTime) {}

GameMode* GameMode::GetInstance()
{
	const EntityManager& entityManager = EntityManager::Get();
	return entityManager.GetGameMode();
}
