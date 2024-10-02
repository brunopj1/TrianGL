#include "AnimationTester.h"

#include "Assets/Animation.h"
#include "WindowConstants.h"
#include <format>

#ifdef IMGUI
#include <imgui.h>
#endif

using namespace TGL;

AnimationTester::AnimationTester(const std::vector<SharedPtr<Sprite>>& sprites)
	: Entity(true), m_AnimationId(s_NextId++)
{
	s_Instances.push_back(this);

	m_Animation = Animation::Create();

	for (const auto& sprite : sprites)
	{
		m_Animation->AddFrame(sprite, 0.15f);
	}

	m_WindowPos = window_padding; // Padding from the top left corner
	m_WindowPos.x += (animation_window_size.x + window_padding.x) * (m_AnimationId - 1); // Skip the previous animation windows horizontally
}

void AnimationTester::OnUpdate(const f32 deltaTime)
{
	RenderAnimationWindow();
}

void AnimationTester::RenderAnimationWindow()
{
#ifdef IMGUI
	ImGui::SetNextWindowPos(ImVec2(m_WindowPos.x, m_WindowPos.y), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(animation_window_size.x, animation_window_size.y), ImGuiCond_Appearing);

	if (ImGui::Begin(std::format("Animation {}", m_AnimationId).c_str()))
	{
		for (i32 i = 0; i < m_Animation->GetFrameCount(); i++)
		{
			ImGui::Text("Frame %d: %.3f seconds", i, m_Animation->GetFrame(i)->GetDuration());
		}
	}

	ImGui::End();
#endif
}

void AnimationTester::RenderAnimationSelector(Animator* animator, i32& currentAnimationId)
{
#ifdef IMGUI
	if (ImGui::RadioButton("None", currentAnimationId == 0))
	{
		currentAnimationId = 0;
		animator->SetAnimation(nullptr);
	}

	for (i32 i = 0; i < s_Instances.size(); i++)
	{
		const i32 animationId = i + 1;
		if (ImGui::RadioButton(std::format("Animation {}", i + 1).c_str(), currentAnimationId == animationId))
		{
			currentAnimationId = animationId;
			animator->SetAnimation(s_Instances[i]->m_Animation);
		}
	}
#endif
}
