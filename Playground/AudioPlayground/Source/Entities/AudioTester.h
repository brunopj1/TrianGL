#pragma once

#include "Assets/Audio.h"
#include "Game/Entity.h"

class AudioTester final : public TGL::Entity
{
private:
	static inline i32 s_NextId = 1;
	static inline std::vector<AudioTester*> s_Instances;

private:
	TGL::SharedPtr<TGL::Audio> m_Audio;
	i32 m_AudioId;

private:
	glm::vec2 m_WindowPos;

public:
	AudioTester(const std::string& path, bool stream = false);
	~AudioTester() override = default;

protected:
	void OnUpdate(f32 deltaTime) override;

public:
	static void RenderAudioSelector(TGL::AudioPlayer* audioPlayer, i32& currentAudioId);
};
