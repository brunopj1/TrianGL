#pragma once

#include "Game/Entity.h"
#include "Implementations/Components/SpriteRenderer.h"
#include "Implementations/Components/Animator.h"
#include "Services/AssetCollection.h"

class Player final : public TGL::Entity
{
private:
	f32 m_Speed = 2.5f;
	
private:
	glm::ivec2 m_LookDirection = { 0, -1 };
	glm::ivec2 m_MoveDirection = { 0, 0 };

private:
	TGL::SpriteRenderer* m_SpriteRenderer;
	TGL::Animator* m_Animator;

private:
	AssetCollection* m_AssetCollection;
	
public:
	Player(AssetCollection& assetCollection);
	~Player() override = default;

public:
	void OnUpdate(f32 deltaTime) override;
};
