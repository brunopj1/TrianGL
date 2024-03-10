#include "GameMode.h"

#include "Core/EntityManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Game;

GameMode::GameMode()
{
    ASSERT_SPAWNER_USAGE(Engine::Game::GameMode, true);
}

GameMode::~GameMode()
{
    ASSERT_SPAWNER_USAGE(Engine::Game::GameMode, false);
}

void GameMode::OnStart() {}

void GameMode::OnEarlyUpdate(float deltaTime) {}

void GameMode::OnLateUpdate(float deltaTime) {}

GameMode* GameMode::GetInstance()
{
    return Core::EntityManager::GetGameMode();
}

void GameMode::Destroy() const
{
    Core::EntityManager::SetGameMode(nullptr);

    PREPARE_SPAWNER_USAGE();

    delete this;
}
