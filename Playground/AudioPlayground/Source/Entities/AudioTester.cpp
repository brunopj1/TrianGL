#include "AudioTester.h"

#include "Implementations/Components/AudioPlayer.h"
#include "WindowConstants.h"

#ifdef IMGUI
#include <format>
#include <imgui.h>
#endif

using namespace TGL;

AudioTester::AudioTester(const std::string& path, const bool stream)
	: Entity(true), m_AudioId(s_NextId++)
{
	s_Instances.push_back(this);

	m_Audio = Audio::Load(path, stream);

	m_WindowPos = window_padding; // Padding from the top left corner
	m_WindowPos.x += (audio_window_size.x + window_padding.x) * (m_AudioId - 1); // Skip the previous audio windows horizontally
}

void AudioTester::OnUpdate(f32 deltaTime)
{
#ifdef IMGUI
	ImGui::SetNextWindowPos(ImVec2(m_WindowPos.x, m_WindowPos.y), ImGuiCond_Appearing);
	ImGui::SetNextWindowSize(ImVec2(audio_window_size.x, audio_window_size.y), ImGuiCond_Appearing);

	if (ImGui::Begin(std::format("Audio {}", m_AudioId).c_str()))
	{
		ImGui::Text("Streamed: ");
		ImGui::SameLine();
		ImGui::TextDisabled(m_Audio->IsStreamed() ? "Yes" : "No");

		ImGui::Separator();

		f32 volume = m_Audio->GetVolume();
		if (ImGui::SliderFloat("Volume", &volume, 0.0f, 5.0f))
		{
			m_Audio->SetVolume(volume);
		}
	}

	ImGui::End();
#endif
}

void AudioTester::RenderAudioSelector(AudioPlayer* audioPlayer, i32& currentAudioId)
{
#ifdef IMGUI
	if (ImGui::RadioButton("None", currentAudioId == 0))
	{
		currentAudioId = 0;
		audioPlayer->SetAudio(nullptr);
	}

	for (i32 i = 0; i < s_Instances.size(); i++)
	{
		const i32 audioId = i + 1;
		if (ImGui::RadioButton(std::format("Audio {}", i + 1).c_str(), currentAudioId == audioId))
		{
			currentAudioId = audioId;
			audioPlayer->SetAudio(s_Instances[i]->m_Audio);
		}
	}
#endif
}
