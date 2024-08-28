#include "AudioPlayerTester.h"

#include "AudioTester.h"
#include "WindowConstants.h"

#ifdef IMGUI
#include <imgui.h>
#include <format>
#endif

using namespace TGL;


AudioPlayerTester::AudioPlayerTester()
    : Entity(true), m_AudioPlayerId(s_NextId++)
{
    s_Instances.push_back(this);

    m_AudioPlayer = AttachComponent<AudioPlayer>();

    m_WindowPos = window_padding * glm::vec2(1, 2); // Padding from the top left corner
    m_WindowPos.y += audio_window_size.y; // Skip the audio window vertically
    m_WindowPos.x += (audio_player_window_size.x + window_padding.x) * (m_AudioPlayerId - 1); // Skip the previous audio player windows horizontally
}

void AudioPlayerTester::OnUpdate(f32 deltaTime)
{
#ifdef IMGUI
    ImGui::SetNextWindowPos(ImVec2(m_WindowPos.x, m_WindowPos.y), ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(ImVec2(audio_player_window_size.x, audio_player_window_size.y), ImGuiCond_Appearing);

    if (ImGui::Begin(std::format("Audio Player {}", m_AudioPlayerId).c_str()))
    {
        ImGui::Text("Status: ");
        ImGui::SameLine();

        switch (m_AudioPlayer->GetStatus())
        {
            case AudioPlayerStatus::Stopped: ImGui::TextDisabled("Stopped");
                break;
            case AudioPlayerStatus::Playing: ImGui::TextDisabled("Playing");
                break;
            case AudioPlayerStatus::Paused: ImGui::TextDisabled("Paused");
                break;
        }

        ImGui::Separator();

        AudioTester::RenderAudioSelector(m_AudioPlayer, m_AudioId);

        ImGui::Separator();

        if (ImGui::Button("Play")) m_AudioPlayer->Play();
        ImGui::SameLine();
        if (ImGui::Button("Pause")) m_AudioPlayer->Pause();
        ImGui::SameLine();
        if (ImGui::Button("Stop")) m_AudioPlayer->Stop();

        ImGui::Separator();

        f32 volume = m_AudioPlayer->GetVolume();
        if (ImGui::SliderFloat("Volume", &volume, 0.0f, 5.0f))
        {
            m_AudioPlayer->SetVolume(volume);
        }

        bool loop = m_AudioPlayer->GetLoop();
        if (ImGui::Checkbox("Loop", &loop))
        {
            m_AudioPlayer->SetLoop(loop);
        }
    }

    ImGui::End();
#endif
}
