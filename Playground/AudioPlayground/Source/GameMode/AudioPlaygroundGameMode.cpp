#include "AudioPlaygroundGameMode.h"

#include "Entities/AudioPlayerTester.h"
#include "Entities/AudioTester.h"
#include <General/Camera.h>

using namespace TGL;

AudioPlaygroundGameMode::AudioPlaygroundGameMode()
{
	Camera* camera = SpawnEntity<Camera>(true);

	SpawnEntity<AudioTester>("Assets/Audio/sound1.wav");
	SpawnEntity<AudioTester>("Assets/Audio/sound2.wav");
	SpawnEntity<AudioTester>("Assets/Audio/sound3.wav");
	SpawnEntity<AudioTester>("Assets/Audio/sound4.wav");
	SpawnEntity<AudioTester>("Assets/Audio/music.mp3", true);

	SpawnEntity<AudioPlayerTester>();
	SpawnEntity<AudioPlayerTester>();
}
