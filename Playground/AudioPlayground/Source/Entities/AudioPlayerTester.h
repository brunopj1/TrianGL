#pragma once

#include "Game/Entity.h"
#include "Implementations/Components/AudioPlayer.h"

class AudioPlayerTester final : public TGL::Entity
{
private:
	static inline i32 s_NextId = 1;
	static inline std::vector<AudioPlayerTester*> s_Instances;

private:
	TGL::AudioPlayer* m_AudioPlayer;
	i32 m_AudioPlayerId;
	i32 m_AudioId = 0;

private:
	glm::vec2 m_WindowPos;

public:
	AudioPlayerTester();
	~AudioPlayerTester() override = default;

protected:
	void OnUpdate(f32 deltaTime) override;

private:
	void RenderAudioPlayerWindow();
};
