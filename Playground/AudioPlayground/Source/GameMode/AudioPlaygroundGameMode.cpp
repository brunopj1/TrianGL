#include "AudioPlaygroundGameMode.h"

#include "Entities/AudioPlayerTester.h"
#include "Entities/SoundTester.h"
#include "Implementations/Entities/Camera.h"

using namespace TGL;

AudioPlaygroundGameMode::AudioPlaygroundGameMode()
{
    Camera* camera = SpawnEntity<Camera>(true);

    SpawnEntity<SoundTester>("Assets/Audio/sound1.wav");
    SpawnEntity<SoundTester>("Assets/Audio/sound2.wav");
    SpawnEntity<SoundTester>("Assets/Audio/sound3.wav");
    SpawnEntity<SoundTester>("Assets/Audio/sound4.wav");

    SpawnEntity<AudioPlayerTester>();
    SpawnEntity<AudioPlayerTester>();
}
