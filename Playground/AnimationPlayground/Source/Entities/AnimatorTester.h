#pragma once

#include "Core/DataTypes.h"
#include "Game/Entity.h"
#include "Implementations/Components/Animator.h"
#include <vector>

class AnimatorTester final : public TGL::Entity
{
private:
	static inline std::vector<AnimatorTester*> s_Instances;
	static inline u32 s_NextId = 1;

private:
	TGL::Animator* m_Animator;
	i32 m_AnimatorId;
	i32 m_AnimationId = 0;

private:
	glm::vec2 m_WindowPos;

public:
	AnimatorTester(const glm::vec2& position);
	~AnimatorTester() override = default;

protected:
	void OnUpdate(f32 deltaTime) override;

private:
	void RenderAnimatorWindow();
};
