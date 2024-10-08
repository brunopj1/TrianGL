﻿#pragma once

#include <Game/Entity.h>

namespace TGL
{
	class GameMode : public GameObject
	{
	private:
		friend class Application;
		friend class EntityManager;

	protected:
		GameMode(i32 orderOfExecution = 0);
		~GameMode() override;

	protected:
		virtual void OnEarlyUpdate(f32 deltaTime);
		virtual void OnLateUpdate(f32 deltaTime);

	public:
		static GameMode* GetInstance();
	};
}
