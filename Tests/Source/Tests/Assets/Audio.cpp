#include "Assets/Audio.h"

#include "Exceptions/Common/FileNotFoundException.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

BEGIN_GAME_TEST(Audio, Load)
{
	void OnUpdate(f32 deltaTime) override
	{
		const SharedPtr<Audio> audio1 = Audio::Load("Assets/Audio/test.wav", false);
		EXPECT_NE(audio1.Get(), nullptr);
		EXPECT_EQ(audio1->IsStreamed(), false);

		const SharedPtr<Audio> audio2 = Audio::Load("Assets/Audio/test.wav", true);
		EXPECT_NE(audio2.Get(), nullptr);
		EXPECT_EQ(audio2->IsStreamed(), true);

		EXPECT_THROW(Audio::Load("Assets/Audio/invalid.wav", false), FileNotFoundException);

		EndTest();
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST(Audio, Volume)
{
	void OnUpdate(f32 deltaTime) override
	{
		SharedPtr<Audio> audio = Audio::Load("Assets/Audio/test.wav", false);
		EXPECT_NE(audio.Get(), nullptr);

		EXPECT_NEAR(audio->GetVolume(), 1.0f, 0.0001f);

		audio->SetVolume(0.5f);
		EXPECT_NEAR(audio->GetVolume(), 0.5f, 0.0001f);

		audio->SetVolume(2.25f);
		EXPECT_NEAR(audio->GetVolume(), 2.25f, 0.0001f);

		audio->SetVolume(-0.5f);
		EXPECT_EQ(audio->GetVolume(), 0.0f);

		EndTest();
	}
}
END_GAME_TEST()
