#pragma once

#include "Core/DataTypes.h"
#include "Entities/AnimationTester.h"
#include "Game/GameMode.h"

class AnimationPlaygroundGameMode final : public TGL::GameMode
{
public:
	AnimationPlaygroundGameMode();
	~AnimationPlaygroundGameMode() override = default;
};
