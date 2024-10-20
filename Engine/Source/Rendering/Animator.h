#pragma once

#include "Assets/AnimationSprite.h"
#include "Game/Component.h"
#include "Memory/SharedPtr.h"

namespace TGL
{
	enum class AnimatorStatus : u8
	{
		Playing,
		Paused,
		Stopped
	};

	// TODO speed
	// TODO OnAnimationEnd event / callback

	class Animator : public Component // NOLINT(CppClassCanBeFinal)
	{
	private:
		friend class SpriteUniform;

	private:
		SharedPtr<AnimationSprite> m_AnimationSprite = nullptr;
		SharedPtr<Animation> m_Animation = nullptr;

	private:
		AnimatorStatus m_Status = AnimatorStatus::Stopped;

	private:
		f32 m_CurrentTime = 0.0f;
		bool m_Loop = false;

	public:
		Animator();
		~Animator() override = default;

	public:
		void SetAnimation(SharedPtr<Animation> animation);
		SharedPtr<Animation> GetAnimation() const;

	public:
		SharedPtr<AnimationSprite> GetAnimationSprite() const;

	public:
		AnimatorStatus GetStatus() const;

	public:
		void Play();
		void Pause();
		void Stop();

	public:
		f32 GetTime() const;
		void JumpToTime(f32 time);

	public:
		void ApplyCurrentFrame();

	public:
		bool GetLoop() const;
		void SetLoop(bool loop);

	protected:
		void OnUpdate(f32 deltaTime) override;
	};

}
