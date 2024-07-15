#include <Assets/Audio.h>

#include <soloud_wav.h>
#include <soloud_wavstream.h>
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

    AssetManager::UnloadAudio(this);
}

SharedPtr<Audio> Audio::Load(const std::string& filePath, const bool stream)
{
    return AssetManager::LoadAudio(filePath, stream);
}

bool Audio::IsStreamed() const
{
    return m_Streamed;
}

f32 Audio::GetVolume() const
{
    return m_SoloudAudio->mVolume;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void Audio::SetVolume(const f32 volume)
{
    m_SoloudAudio->mVolume = volume < 0.0f ? 0.0f : volume;

    for (const AudioPlayer* player : m_CurrentPlayers)
    {
        player->UpdateCurrentAudioVolume();
    }
}

void Audio::Init()
{
    SoLoud::result result;

    if (m_Streamed)
    {
        SoLoud::WavStream* soloudAudio = new SoLoud::WavStream();
        result = soloudAudio->load(m_FilePath.c_str());
        m_SoloudAudio = soloudAudio;
    }
    else
    {
        SoLoud::Wav* soloudAudio = new SoLoud::Wav();
        result = soloudAudio->load(m_FilePath.c_str());
        m_SoloudAudio = soloudAudio;
    }

    if (result != SoLoud::SO_NO_ERROR)
    {
        delete m_SoloudAudio;
        m_SoloudAudio = nullptr;

        throw FileNotFoundException(m_FilePath);
    }
}

void Audio::Free()
{
    delete m_SoloudAudio;
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
