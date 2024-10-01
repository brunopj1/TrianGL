#pragma once

#include "Internal/Sprite.h"
#include "Memory/SharedPtr.h"
#include <vector>

namespace TGL
{
	class AnimationFrame final
	{
	private:
		friend class Animation;

	private:
		Animation* m_Animation; // TODO replace with a weak pointer (remove the variable updates and null checks)
		SharedPtr<Sprite> m_Sprite;
		f32 m_Duration;

	public:
		AnimationFrame(Animation* animation, SharedPtr<Sprite> sprite, f32 duration);
		~AnimationFrame();

	public:
		SharedPtr<Sprite> GetSprite() const;
		f32 GetDuration() const;
	};

	class Animation final
	{
	private:
		friend class Animator;
		friend class AnimationFrame;

	private:
		std::vector<SharedPtr<AnimationFrame>> m_Frames;
		f32 m_DefaultDuration = 0.0f;
		f32 m_AlternativeDuration = 0.0f;

	public:
		Animation();
		~Animation();

	public:
		static SharedPtr<Animation> Create();

	public:
		SharedPtr<AnimationFrame> AddFrame(SharedPtr<Sprite> sprite, f32 duration, i32 index = -1);
		SharedPtr<AnimationFrame> GetFrame(u32 index) const;
		u32 GetFrameCount() const;

	public:
		f32 GetDefaultDuration() const;
		bool IsUsingDefaultDuration() const;
		void UseDefaultDuration();

	public:
		f32 GetDuration() const;
		void SetDuration(f32 duration);

	private:
		SharedPtr<Sprite> GetSpriteAtTime(f32 time) const;

	private:
		void UpdateDefaultDuration();
	};
}
