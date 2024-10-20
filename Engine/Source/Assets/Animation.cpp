#include "Animation.h"

#include "Core/Services/Private/AssetManager.h"
#include <stdexcept>
#include <utility>

using namespace TGL;

AnimationFrame::AnimationFrame(Animation* animation, SharedPtr<Sprite> sprite, const f32 duration)
	: m_Animation(animation), m_Sprite(std::move(sprite)), m_Duration(duration)
{
	ASSERT_ASSET_FACTORY_CONSTRUCTOR(AnimationFrame);

	if (m_Sprite == nullptr)
	{
		throw std::invalid_argument("The sprite cannot be null");
	}

	if (duration <= 0.0f)
	{
		throw std::invalid_argument("The duration must be greater than zero");
	}
}

AnimationFrame::~AnimationFrame()
{
	ASSERT_ASSET_FACTORY_DESTRUCTOR();
}

SharedPtr<Sprite> AnimationFrame::GetSprite() const
{
	return m_Sprite;
}

f32 AnimationFrame::GetDuration() const
{
	return m_Duration;
}

Animation::Animation()
{
	ASSERT_ASSET_FACTORY_CONSTRUCTOR(Animation);
}

Animation::~Animation()
{
	ASSERT_ASSET_FACTORY_DESTRUCTOR();

	for (SharedPtr<AnimationFrame>& frame : m_Frames)
	{
		frame->m_Animation = nullptr;
	}
}

SharedPtr<Animation> Animation::Create()
{
	AssetManager& assetManager = AssetManager::Get();
	return assetManager.CreateAnimation();
}

SharedPtr<AnimationFrame> Animation::AddFrame(SharedPtr<Sprite> sprite, const f32 duration, const i32 index)
{
	const i32 frameCount = static_cast<i32>(m_Frames.size());

	if (index > frameCount)
	{
		throw std::invalid_argument("Index out of range");
	}

	const u32 normalizedIndex = index < 0 ? frameCount : index;

	AssetManager& assetManager = AssetManager::Get();
	const SharedPtr<AnimationFrame> frame = assetManager.CreateAnimationFrame(this, std::move(sprite), duration);

	m_Frames.insert(m_Frames.begin() + normalizedIndex, frame);

	UpdateDefaultDuration();

	return frame;
}

SharedPtr<AnimationFrame> Animation::GetFrame(const u32 index) const
{
	const u32 frameCount = static_cast<u32>(m_Frames.size());

	if (index >= frameCount)
	{
		throw std::invalid_argument("Index out of range");
	}

	return m_Frames[index];
}

u32 Animation::GetFrameCount() const
{
	return static_cast<u32>(m_Frames.size());
}

f32 Animation::GetDefaultDuration() const
{
	return m_DefaultDuration;
}

bool Animation::IsUsingDefaultDuration() const
{
	return m_AlternativeDuration == 0.0f;
}

void Animation::UseDefaultDuration()
{
	m_AlternativeDuration = 0.0f;
}

f32 Animation::GetDuration() const
{
	return IsUsingDefaultDuration() ? m_DefaultDuration : m_AlternativeDuration;
}

void Animation::SetDuration(const f32 duration)
{
	if (duration <= 0.0f)
	{
		throw std::invalid_argument("The duration must be greater than zero");
	}

	m_AlternativeDuration = duration;
}
SharedPtr<Sprite> Animation::GetSpriteAtTime(f32 time) const
{
	// If the animation is empty
	if (m_Frames.empty())
	{
		return nullptr;
	}

	// Adapt the time to the default animation duration
	if (!IsUsingDefaultDuration())
	{
		time = time / m_AlternativeDuration * m_DefaultDuration;
	}

	for (auto& frame : m_Frames)
	{
		time -= frame->GetDuration();

		if (time <= 0.0f)
		{
			return frame->GetSprite();
		}
	}

	return nullptr;
}

void Animation::UpdateDefaultDuration()
{
	m_DefaultDuration = 0.0f;

	for (const SharedPtr<AnimationFrame>& frame : m_Frames)
	{
		m_DefaultDuration += frame->GetDuration();
	}
}
