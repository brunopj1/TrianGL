#pragma once

#include "Game/Entity.h"
#include "Implementations/Components/AudioPlayer.h"

class AudioPlayerTester final : public TGL::Entity
{
private:
    static inline int s_NextId = 1;
    static inline std::vector<AudioPlayerTester*> s_Instances;

private:
    TGL::AudioPlayer* m_AudioPlayer;
    int m_AudioPlayerId;
    int m_SoundId = 0;

public:
    AudioPlayerTester();
    ~AudioPlayerTester() override = default;

protected:
    void OnUpdate(float deltaTime) override;
};
