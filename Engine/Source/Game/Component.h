#pragma once

#include <Game/Entity.h>

namespace TGL
{
	class Component : public GameObject
	{
	private:
		friend class EntityManager;
		friend class Entity;

	private:
		Entity* m_Parent = nullptr;

	protected:
		Component(bool shouldUpdate, i32 orderOfExecution = 0);
		~Component() override;

	public:
		Entity* GetParent() const;

	public:
		void Detach();
	};
}
