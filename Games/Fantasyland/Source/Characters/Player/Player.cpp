#include "Player.h"

#include "Core/Services/Public/InputSystem.h"

using namespace TGL;

Player::Player(AssetCollection& assetCollection)
	: Entity(true), m_AssetCollection(&assetCollection)
{
	m_SpriteRenderer = AttachComponent<SpriteRenderer>();
	SharedPtr<DefaultSpriteMaterial> material = m_SpriteRenderer->UseDefaultMaterial();

	m_Animator = AttachComponent<Animator>();
	m_Animator->SetLoop(true);
	material->Sprite->Value = m_Animator->GetAnimationSprite();

	m_Animator->SetAnimation(m_AssetCollection->GetPlayerIdleAnimation(m_LookDirection));
	m_Animator->Play();
}

void Player::OnUpdate(const f32 deltaTime)
{
	const InputSystem& inputSystem = InputSystem::Get();

	glm::ivec2 newDirection;
	newDirection.x = inputSystem.IsKeyDown(KeyCode::D) - inputSystem.IsKeyDown(KeyCode::A);
	newDirection.y = inputSystem.IsKeyDown(KeyCode::W) - inputSystem.IsKeyDown(KeyCode::S);

	if (newDirection != m_MoveDirection)
	{
		m_MoveDirection = newDirection;

		if (newDirection != glm::ivec2(0))
		{
			m_LookDirection = newDirection;

			m_Animator->SetAnimation(m_AssetCollection->GetPlayerWalkAnimation(m_LookDirection));
		}
		else
		{
			m_Animator->SetAnimation(m_AssetCollection->GetPlayerIdleAnimation(m_LookDirection));
		}

		m_Animator->Play();
	}

	if (m_MoveDirection != glm::ivec2(0))
	{
		const glm::vec2 normDirection = glm::normalize(glm::vec2(m_MoveDirection));
		GetTransform().TranslateBy(normDirection * m_Speed * deltaTime);
	}
}
