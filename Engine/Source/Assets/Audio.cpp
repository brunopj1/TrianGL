#include "Core/Internal/AudioLayer.h"
#include <Assets/Audio.h>

#include <Core/AssetManager.h>
#include <Exceptions/Common/FileNotFoundException.h>
#include <Implementations/Components/AudioPlayer.h>
#include <Internal/Asserts/SpawnerAsserts.h>

using namespace TGL;

Audio::Audio(std::string filePath, const bool stream)
    : m_FilePath(std::move(filePath)), m_Streamed(stream)
{
    ASSERT_SPAWNER_USAGE_CONSTRUCTOR(TGL::AssetManager, Audio);
}

Audio::~Audio()
{
    ASSERT_SPAWNER_USAGE_DESTRUCTOR(TGL::SharedPtrSpawnerUtil, Asset);

    AssetManager& assetManager = AssetManager::Get();
    assetManager.UnloadAudio(this);
}

SharedPtr<Audio> Audio::Load(const std::string& filePath, const bool stream)
{
    AssetManager& assetManager = AssetManager::Get();
    return assetManager.LoadAudio(filePath, stream);
}

bool Audio::IsStreamed() const
{
    return m_Streamed;
}

f32 Audio::GetVolume() const
{
    return AudioLayer::GetAudioVolume(m_SoloudAudio);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void Audio::SetVolume(const f32 volume)
{
    const f32 clampedVolume = volume < 0.0f ? 0.0f : volume;

    AudioLayer::SetAudioVolume(m_SoloudAudio, clampedVolume);

    for (const AudioPlayer* player : m_CurrentPlayers)
    {
        player->UpdateCurrentAudioVolume();
    }
}

void Audio::Init()
{
    m_SoloudAudio = AudioLayer::LoadAudio(m_FilePath, m_Streamed);

    if (m_SoloudAudio == nullptr)
    {
        throw FileNotFoundException(m_FilePath);
    }
}

void Audio::Free()
{
    AudioLayer::UnloadAudio(m_SoloudAudio);
    m_SoloudAudio = nullptr;
}

void Audio::AddPlayer(AudioPlayer* player)
{
    m_CurrentPlayers.push_back(player);
}

void Audio::RemovePlayer(AudioPlayer* player)
{
    std::erase(m_CurrentPlayers, player);
}
