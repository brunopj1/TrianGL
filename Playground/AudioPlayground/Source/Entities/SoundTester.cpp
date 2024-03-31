#include "SoundTester.h"

#include <format>
#include "WindowConstants.h"
#include "Implementations/Components/AudioPlayer.h"
#include <imgui.h>

using namespace TGL;

SoundTester::SoundTester(const std::string& path)
    : Entity(true), m_SoundId(s_NextId++)
{
    s_Instances.push_back(this);

    m_Sound = Sound::Load(path);
}

void SoundTester::OnUpdate(float deltaTime)
{
    ImGui::SetNextWindowPos(window_padding + (sound_window_size + window_padding) * ImVec2(m_SoundId - 1, 0), ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(sound_window_size, ImGuiCond_Appearing);

    if (ImGui::Begin(std::format("Sound {}", m_SoundId).c_str()))
    {
        float volume = m_Sound->GetVolume();
        if (ImGui::SliderFloat("Volume", &volume, 0.0f, 5.0f))
        {
            m_Sound->SetVolume(volume);
        }
    }

    ImGui::End();
}

void SoundTester::RenderSoundSelector(AudioPlayer* audioPlayer, int& currentSoundId)
{
    if (ImGui::RadioButton("None", currentSoundId == 0))
    {
        currentSoundId = 0;
        audioPlayer->SetSound(nullptr);
    }

    for (int i = 0; i < s_Instances.size(); i++)
    {
        const int soundId = i + 1;
        if (ImGui::RadioButton(std::format("Sound {}", i + 1).c_str(), currentSoundId == soundId))
        {
            currentSoundId = soundId;
            audioPlayer->SetSound(s_Instances[i]->m_Sound);
        }
    }
}
