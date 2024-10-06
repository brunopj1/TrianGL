#include <Core/Services/Private/EntityManager.h>
#include <Game/GameMode.h>

using namespace TGL;

GameMode::GameMode(const i32 orderOfExecution)
	: GameObject(true, orderOfExecution)
{
	ASSERT_ENTITY_FACTORY_CONSTRUCTOR(GameMode);
}

GameMode::~GameMode()
{
	ASSERT_ENTITY_FACTORY_DESTRUCTOR(GameMode);
}

void GameMode::OnEarlyUpdate(f32 deltaTime) {}

void GameMode::OnLateUpdate(f32 deltaTime) {}

GameMode* GameMode::GetInstance()
{
	const EntityManager& entityManager = EntityManager::Get();
	return entityManager.GetGameMode();
}
