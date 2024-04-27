#pragma once

#include "Game/Entity.h"
#include "Assets/Audio.h"

class AudioTester final : public TGL::Entity
{
private:
    static inline int s_NextId = 1;
    static inline std::vector<AudioTester*> s_Instances;

private:
    TGL::SharedPtr<TGL::Audio> m_Audio;
    int m_AudioId;

private:
    glm::vec2 m_WindowPos;

public:
    AudioTester(const std::string& path, bool stream = false);
    ~AudioTester() override = default;

protected:
    void OnUpdate(float deltaTime) override;

public:
    static void RenderAudioSelector(TGL::AudioPlayer* audioPlayer, int& currentAudioId);
};
