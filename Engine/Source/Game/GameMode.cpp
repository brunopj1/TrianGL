#include "GameMode.h"

#include "Core/EntityManager.h"
#include "Util/DebugFeatures.hpp"

using namespace Engine::Game;

GameMode::GameMode()
{
    DEBUG_SINGLETON_ASSERT_USAGE(Engine::Core::EntityManager, "Engine::Game::GameMode");
}

GameMode::~GameMode()
{
#pragma warning(suppress: 4297) // Supress the "function assumed not to throw an exception" warning
    DEBUG_SINGLETON_ASSERT_USAGE(Engine::Core::EntityManager, "Engine::Game::GameMode");
}

void GameMode::OnStart() {}

void GameMode::OnEarlyUpdate() {}

void GameMode::OnLateUpdate() {}
