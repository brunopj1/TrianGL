#include "GameMode.h"

#include "Services/EntityManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Game;

GameMode::GameMode()
{
    ASSERT_SPAWNER_USAGE(Engine::Game::GameMode, Engine::Game::GameMode, true);
}

GameMode::~GameMode()
{
    ASSERT_SPAWNER_USAGE(Engine::Game::GameMode, Engine::Game::GameMode, false);
}

void GameMode::OnStart() {}

void GameMode::OnEarlyUpdate(float deltaTime) {}

void GameMode::OnLateUpdate(float deltaTime) {}

GameMode* GameMode::GetInstance()
{
    return Services::EntityManager::GetGameMode();
}

void GameMode::Destroy() const
{
    Services::EntityManager::SetGameMode(nullptr);

    PREPARE_SPAWNER_USAGE();

    delete this;
}
