﻿#include "AudioPlayerTester.h"

#include "AudioTester.h"
#include "WindowConstants.h"
#include <format>
#include <imgui.h>

using namespace TGL;


AudioPlayerTester::AudioPlayerTester()
    : Entity(true), m_AudioPlayerId(s_NextId++)
{
    s_Instances.push_back(this);

    m_AudioPlayer = AttachComponent<AudioPlayer>();
}

void AudioPlayerTester::OnUpdate(float deltaTime)
{
    ImGui::SetNextWindowPos(window_padding * ImVec2(1, 2) + ImVec2(0, audio_window_size.y) + (audio_player_window_size + window_padding) * ImVec2(m_AudioPlayerId - 1, 0), ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(audio_player_window_size, ImGuiCond_Appearing);

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

        float volume = m_AudioPlayer->GetVolume();
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
}