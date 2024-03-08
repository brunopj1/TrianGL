﻿#include "GameMode.h"

#include "Services/EntityManager.h"
#include "Util/Macros/SingletonMacros.hpp"

using namespace Engine::Game;

GameMode::GameMode()
{
    ASSERT_SINGLETON_USAGE(Engine::Services::EntityManager, Engine::Game::GameMode, true);
}

GameMode::~GameMode()
{
#pragma warning(suppress: 4297) // Supress the "function assumed not to throw an exception" warning
    ASSERT_SINGLETON_USAGE(Engine::Services::EntityManager, Engine::Game::GameMode, false);
}

void GameMode::OnStart() {}

void GameMode::OnEarlyUpdate(float deltaTime) {}

void GameMode::OnLateUpdate(float deltaTime) {}
