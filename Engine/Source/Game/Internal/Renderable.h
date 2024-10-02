#pragma once

#include "Core/DataTypes.h"
#include "Game/Transform.h"

namespace TGL
{
	class Renderable
	{
	private:
		friend class EntityManager;

	private:
		i32 m_ZIndex = 0;
		Transform m_Transform;

	protected:
		Renderable() = default;
		virtual ~Renderable() = default;

	public:
		Transform& GetTransform();
		const Transform& GetTransform() const;
		
	public:
		i32 GetZIndex() const;
		void SetZIndex(i32 zIndex);

	protected:
		virtual void Render() = 0;
	};
}
