#pragma once

#include "Characters/Player/Player.h"
#include "Game/GameMode.h"
#include "Implementations/Entities/Camera.h"
#include "Services/AssetCollection.h"

class FantasylandGameMode final : public TGL::GameMode
{
private:
	AssetCollection m_AssetCollection;
	
private:
	TGL::Camera* m_Camera;
	Player* m_Player;
	
public:
    FantasylandGameMode();
    ~FantasylandGameMode() override = default;
};