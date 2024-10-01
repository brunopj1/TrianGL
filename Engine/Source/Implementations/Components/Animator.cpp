#include "Animator.h"

#include "Assets/Animation.h"
#include <stdexcept>

using namespace TGL;

Animator::Animator()
	: Component(true)
{}

Animator::~Animator()
{
	// Set the target uniform to nullptr to remove this animator from the active animators map
	SetTargetUniform(nullptr);
}

void Animator::SetAnimation(SharedPtr<Animation> animation)
{
	if (m_Animation == animation)
	{
		return;
	}

	Stop();

	m_Animation = std::move(animation);
}

SharedPtr<Animation> Animator::GetAnimation() const
{
	return m_Animation;
}

void Animator::SetTargetUniform(SpriteUniform* spriteUniform)
{
	if (m_TargetUniform == spriteUniform)
	{
		return;
	}

	// Check if the new uniform is already being used by another animator
	if (spriteUniform != nullptr && s_ActiveAnimators.contains(spriteUniform))
	{
		throw std::invalid_argument("The specified uniform is already being used by a different animator");
	}

	Stop();

	UpdateActiveAnimators(m_TargetUniform, spriteUniform, this);

	m_TargetUniform = spriteUniform;
}

SpriteUniform* Animator::GetTargetUniform() const
{
	return m_TargetUniform;
}

AnimatorStatus Animator::GetStatus() const
{
	return m_Status;
}

void Animator::Play()
{
	if (m_Status == AnimatorStatus::Playing)
	{
		return;
	}

	if (m_Animation == nullptr || m_TargetUniform == nullptr)
	{
		return;
	}

	m_Status = AnimatorStatus::Playing;
}

void Animator::Pause()
{
	if (m_Status != AnimatorStatus::Playing)
	{
		return;
	}

	m_Status = AnimatorStatus::Paused;
}

void Animator::Stop()
{
	if (m_Status == AnimatorStatus::Stopped)
	{
		return;
	}

	m_Status = AnimatorStatus::Stopped;
	m_CurrentTime = 0.0f;
}

f32 Animator::GetTime() const
{
	return m_CurrentTime;
}

void Animator::JumpToTime(const f32 time)
{
	if (m_Animation == nullptr)
	{
		return;
	}

	if (time < 0.0f)
	{
		throw std::invalid_argument("The time must be greater than or equal to zero");
	}

	if (time > m_Animation->GetDuration())
	{
		throw std::invalid_argument("The time must be less than the animation duration");
	}

	m_CurrentTime = time;
}
void Animator::ApplyCurrentFrame()
{
	if (m_Animation == nullptr || m_TargetUniform == nullptr)
	{
		return;
	}

	const SharedPtr<Sprite> currentSprite = m_Animation->GetSpriteAtTime(m_CurrentTime);

	if (currentSprite != nullptr)
	{
		m_TargetUniform->Value = currentSprite;
	}
}

bool Animator::GetLoop() const
{
	return m_Loop;
}

void Animator::SetLoop(const bool loop)
{
	m_Loop = loop;
}

void Animator::OnUpdate(const f32 deltaTime)
{
	if (m_Status != AnimatorStatus::Playing)
	{
		return;
	}

	m_CurrentTime += deltaTime;
	const f32 duration = m_Animation->GetDuration();

	if (m_Loop && m_CurrentTime > duration)
	{
		m_CurrentTime = std::fmod(m_CurrentTime, duration);
	}

	const SharedPtr<Sprite> currentSprite = m_Animation->GetSpriteAtTime(m_CurrentTime);

	if (currentSprite != nullptr)
	{
		m_TargetUniform->Value = currentSprite;
	}
	else
	{
		Stop();
	}
}

void Animator::UpdateActiveAnimators(SpriteUniform* previousTargetUniform, SpriteUniform* newTargetUniform, Animator* animator)
{
	// Remove the previous active animator
	if (previousTargetUniform != nullptr)
	{
		s_ActiveAnimators.erase(previousTargetUniform);
	}

	// Add the new active animator
	if (newTargetUniform != nullptr)
	{
		s_ActiveAnimators[newTargetUniform] = animator;
	}
}

void Animator::RemoveAllActiveAnimators(SpriteUniform* spriteUniform)
{
	if (s_ActiveAnimators.contains(spriteUniform))
	{
		Animator* animator = s_ActiveAnimators[spriteUniform];
		animator->m_TargetUniform = nullptr;

		s_ActiveAnimators.erase(spriteUniform);
	}
}
