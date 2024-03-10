#include "GameMode.h"

#include "Core/EntityManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine;

GameMode::GameMode()
{
    ASSERT_SPAWNER_USAGE(Engine::GameMode, true);
}

GameMode::~GameMode()
{
    ASSERT_SPAWNER_USAGE(Engine::GameMode, false);
}

void GameMode::OnStart() {}

void GameMode::OnEarlyUpdate(float deltaTime) {}

void GameMode::OnLateUpdate(float deltaTime) {}

GameMode* GameMode::GetInstance()
{
    return EntityManager::GetGameMode();
}

void GameMode::Destroy() const
{
    EntityManager::SetGameMode(nullptr);

    PREPARE_SPAWNER_USAGE();

    delete this;
}
