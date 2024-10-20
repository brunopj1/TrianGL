#include "Rendering/AudioPlayer.h"

#include "Assets/Audio.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

// Helper classes

namespace
{
	class TestEntity final : public Entity
	{
	public:
		TestEntity()
			: Entity(false) {}
	};
}

// Mock services

namespace
{
	class MockAudioBackend final : public AudioBackend
	{
	protected:
		bool IsValidAudioHandle(SoLoud::Soloud* soloudEngine, i32 handle) override
		{
			static u32 counter = 5;
			counter--;

			if (counter == 0)
			{
				return false;
			}

			return true;
		}
	};

	void MockServiceBuilder(ServiceCollection& collection)
	{
		collection.CreateService<MockAudioBackend>();
	}
}

// Tests

BEGIN_GAME_TEST(AudioPlayer, PlaybackControls)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		AudioPlayer* audioPlayer = entity->AttachComponent<AudioPlayer>();

		audioPlayer->Play();
		EXPECT_EQ(audioPlayer->GetStatus(), AudioPlayerStatus::Stopped);

		audioPlayer->Pause();
		EXPECT_EQ(audioPlayer->GetStatus(), AudioPlayerStatus::Stopped);

		audioPlayer->Play();
		EXPECT_EQ(audioPlayer->GetStatus(), AudioPlayerStatus::Stopped);

		audioPlayer->Stop();
		EXPECT_EQ(audioPlayer->GetStatus(), AudioPlayerStatus::Stopped);

		const SharedPtr<Audio> audio = Audio::Load("Assets/Audio/test.wav");
		audioPlayer->SetAudio(audio);

		audioPlayer->Play();
		EXPECT_EQ(audioPlayer->GetStatus(), AudioPlayerStatus::Playing);

		audioPlayer->Pause();
		EXPECT_EQ(audioPlayer->GetStatus(), AudioPlayerStatus::Paused);

		audioPlayer->Play();
		EXPECT_EQ(audioPlayer->GetStatus(), AudioPlayerStatus::Playing);

		audioPlayer->Stop();
		EXPECT_EQ(audioPlayer->GetStatus(), AudioPlayerStatus::Stopped);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(AudioPlayer, PlaybackCompletion, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		const Clock& clock = Clock::Get();
		const u32 frame = clock.GetFrameCount();

		static AudioPlayer* audioPlayer = nullptr;

		if (frame == 1)
		{
			TestEntity* entity = SpawnEntity<TestEntity>();
			audioPlayer = entity->AttachComponent<AudioPlayer>();

			const SharedPtr<Audio> audio = Audio::Load("Assets/Audio/test.wav");
			audioPlayer->SetAudio(audio);
			audioPlayer->Play();
		}

		if (frame >= 1 && frame <= 5)
		{
			EXPECT_EQ(audioPlayer->GetStatus(), AudioPlayerStatus::Playing);
		}

		if (frame == 6)
		{
			EXPECT_EQ(audioPlayer->GetStatus(), AudioPlayerStatus::Stopped);

			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(AudioPlayer, Volume)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		AudioPlayer* audioPlayer = entity->AttachComponent<AudioPlayer>();

		SharedPtr<Audio> audio = Audio::Load("Assets/Audio/test.wav");
		audioPlayer->SetAudio(audio);

		audioPlayer->SetPlayerVolume(0.5f);
		EXPECT_NEAR(audioPlayer->GetPlayerVolume(), 0.5f, 0.001f);

		audioPlayer->SetPlayerVolume(1.5f);
		EXPECT_NEAR(audioPlayer->GetPlayerVolume(), 1.50f, 0.001f);

		audioPlayer->SetPlayerVolume(0.0f);
		EXPECT_NEAR(audioPlayer->GetPlayerVolume(), 0.0f, 0.001f);

		audioPlayer->SetPlayerVolume(-0.5f);
		EXPECT_NEAR(audioPlayer->GetPlayerVolume(), 0.0f, 0.001f);

		audioPlayer->SetPlayerVolume(0.5f);
		audio->SetVolume(0.5f);
		EXPECT_NEAR(audioPlayer->GetEffectiveVolume(), 0.25f, 0.001f);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(AudioPlayer, Loop)
{
	void OnUpdate(f32 deltaTime) override
	{
		TestEntity* entity = SpawnEntity<TestEntity>();
		AudioPlayer* audioPlayer = entity->AttachComponent<AudioPlayer>();

		const SharedPtr<Audio> audio = Audio::Load("Assets/Audio/test.wav");
		audioPlayer->SetAudio(audio);

		audioPlayer->SetLoop(true);
		EXPECT_TRUE(audioPlayer->GetLoop());

		audioPlayer->SetLoop(false);
		EXPECT_FALSE(audioPlayer->GetLoop());

		EndTest();
	}
}
END_GAME_TEST()
