#pragma once

#include "Game/Entity.h"
#include "Resources/Sound.h"

class SoundTester final : public TGL::Entity
{
private:
    static inline int s_NextId = 1;
    static inline std::vector<SoundTester*> s_Instances;

private:
    std::shared_ptr<TGL::Sound> m_Sound;
    int m_SoundId;

public:
    SoundTester(const std::string& path);
    ~SoundTester() override = default;

protected:
    void OnUpdate(float deltaTime) override;

public:
    static void RenderSoundSelector(TGL::AudioPlayer* audioPlayer, int& currentSoundId);
};
