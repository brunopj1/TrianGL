#include "Core/Services/Backends/AudioBackend.h"
#include <Assets/Audio.h>
#include <Core/Services/Private/AssetManager.h>
#include <Exceptions/Common/FileNotFoundException.h>
#include <Implementations/Components/AudioPlayer.h>

using namespace TGL;

Audio::Audio(std::string filePath, const bool stream)
	: m_FilePath(std::move(filePath)), m_Streamed(stream)
{
	ASSERT_ASSET_FACTORY_CONSTRUCTOR(Audio);

	Init();
}

Audio::~Audio()
{
	ASSERT_ASSET_FACTORY_DESTRUCTOR();

	Free();
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
	return m_Volume;
}

void Audio::SetVolume(const f32 volume)
{
	m_Volume = volume < 0.0f ? 0.0f : volume;

	AudioBackend& audioBackend = AudioBackend::Get();
	audioBackend.SetAudioVolume(m_SoloudAudio, m_Volume);

	for (const AudioPlayer* player : m_CurrentPlayers)
	{
		player->UpdateCurrentAudioVolume();
	}
}

void Audio::Init()
{
	AudioBackend& audioBackend = AudioBackend::Get();
	m_SoloudAudio = audioBackend.LoadAudio(m_FilePath, m_Streamed);

	if (m_SoloudAudio == nullptr)
	{
		throw FileNotFoundException(m_FilePath);
	}

	// Setup the default audio settings
	SetVolume(m_Volume);
}

void Audio::Free()
{
	AudioBackend& audioBackend = AudioBackend::Get();
	audioBackend.UnloadAudio(m_SoloudAudio);
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
