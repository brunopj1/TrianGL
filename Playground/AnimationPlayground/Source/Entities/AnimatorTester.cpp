#include "AnimatorTester.h"

#include "AnimationTester.h"
#include "Assets/Animation.h"
#include "Implementations/Components/SpriteRenderer.h"
#include "WindowConstants.h"
#include <format>

#ifdef IMGUI
#include <imgui.h>
#endif

using namespace TGL;

AnimatorTester::AnimatorTester(const glm::vec2& position)
	: Entity(true), m_AnimatorId(s_NextId++)
{
	s_Instances.push_back(this);

	GetTransform().SetPosition(position);

	SpriteRenderer* spriteRenderer = AttachComponent<SpriteRenderer>();
	SharedPtr<DefaultSpriteMaterial> material = spriteRenderer->UseDefaultMaterial();

	m_Animator = AttachComponent<Animator>();
	m_Animator->SetTargetUniform(material->Sprite);

	m_WindowPos = window_padding * glm::vec2(1, 2); // Padding from the top left corner
	m_WindowPos.y += animation_window_size.y; // Skip the animation window vertically
	m_WindowPos.x += (animator_window_size.x + window_padding.x) * (m_AnimatorId - 1); // Skip the previous animator windows horizontally
}

void AnimatorTester::OnUpdate(const f32 deltaTime)
{
	RenderAnimatorWindow();
}

void AnimatorTester::RenderAnimatorWindow()
{
#ifdef IMGUI
	ImGui::SetNextWindowPos(ImVec2(m_WindowPos.x, m_WindowPos.y), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(animator_window_size.x, animator_window_size.y), ImGuiCond_Appearing);

	if (ImGui::Begin(std::format("Animator {}", m_AnimatorId).c_str()))
	{
		ImGui::Text("Status: ");
		ImGui::SameLine();

		switch (m_Animator->GetStatus())
		{
			case AnimatorStatus::Stopped:
				ImGui::TextDisabled("Stopped");
				break;
			case AnimatorStatus::Playing:
				ImGui::TextDisabled("Playing");
				break;
			case AnimatorStatus::Paused:
				ImGui::TextDisabled("Paused");
				break;
		}

		ImGui::Separator();

		AnimationTester::RenderAnimationSelector(m_Animator, m_AnimationId);

		ImGui::Separator();

		if (ImGui::Button("Play"))
		{
			m_Animator->Play();
		}
		ImGui::SameLine();
		if (ImGui::Button("Pause"))
		{
			m_Animator->Pause();
		}
		ImGui::SameLine();
		if (ImGui::Button("Stop"))
		{
			m_Animator->Stop();
		}

		ImGui::Separator();

		bool loop = m_Animator->GetLoop();
		if (ImGui::Checkbox("Loop", &loop))
		{
			m_Animator->SetLoop(loop);
		}

		ImGui::Separator();

		const SharedPtr<Animation> animation = m_Animator->GetAnimation();
		f32 currentTime = m_Animator->GetTime();
		const f32 duration = animation != nullptr ? animation->GetDuration() : 0.0f;
		if (ImGui::SliderFloat("Time", &currentTime, 0.0f, duration) && animation != nullptr)
		{
			m_Animator->JumpToTime(currentTime);
		}
	}

	ImGui::End();
#endif
}
