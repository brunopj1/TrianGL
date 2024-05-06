﻿#include <Game/GameMode.h>

#include <Core/EntityManager.h>

using namespace TGL;

GameMode::GameMode()
    : GameObject(true)
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::EntityManager, GameMode);
}

GameMode::~GameMode()
{
    ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::EntityManager, GameMode);
}

void GameMode::OnEarlyUpdate(float deltaTime) {}

void GameMode::OnLateUpdate(float deltaTime) {}

GameMode* GameMode::GetInstance()
{
    return EntityManager::GetGameMode();
}
