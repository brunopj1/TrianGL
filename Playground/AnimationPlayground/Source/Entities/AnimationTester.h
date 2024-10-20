#pragma once

#include "Assets/Internal/Sprite.h"
#include "Game/Entity.h"
#include "Memory/SharedPtr.h"
#include "Rendering/Animator.h"
#include <vector>

class AnimationTester final : public TGL::Entity
{
private:
	friend class AnimatorTester;

private:
	static inline std::vector<AnimationTester*> s_Instances;
	static inline u32 s_NextId = 1;

private:
	TGL::SharedPtr<TGL::Animation> m_Animation;
	i32 m_AnimationId;

private:
	glm::vec2 m_WindowPos;

public:
	AnimationTester(const std::vector<TGL::SharedPtr<TGL::Sprite>>& sprites);
	~AnimationTester() override = default;

protected:
	void OnUpdate(f32 deltaTime) override;

private:
	void RenderAnimationWindow();
	static void RenderAnimationSelector(TGL::Animator* animator, i32& currentAnimationId);
};
