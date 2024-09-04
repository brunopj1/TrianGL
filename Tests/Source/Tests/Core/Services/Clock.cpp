#include "Core/Services/Clock.h"

#include "Core/Application.h"
#include "Core/Services/Window.h"
#include "Game/GameMode.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

TEST_GAME_BEGIN(Clock, TimeProgression)
{
	void OnUpdate(const f32 deltaTime) override
	{
		static i32 lastFrame = 0;
		static f32 lastTime = 0.0f;

		const Clock& clock = Clock::Get();

		// Delta time
		ASSERT_GT(clock.GetDeltaTime(), 0.0f);

		// Total time
		const f32 currentTime = clock.GetTotalTime();

		ASSERT_GT(currentTime, lastTime);
		ASSERT_GE(currentTime, deltaTime);
		ASSERT_GT(currentTime, 0.0f);

		lastTime = currentTime;

		// Frame count
		const i32 currentFrame = clock.GetFrameCount();

		ASSERT_GE(currentFrame, 0);
		ASSERT_EQ(currentFrame, lastFrame + 1);

		lastFrame = currentFrame;

		// New Second
		const bool isNewSecond = clock.IsNewSecond();

		ASSERT_EQ(isNewSecond, currentTime >= 1.0f);

		if (isNewSecond)
		{
			Window::Get().Close();
		}
	}
}
TEST_GAME_END()

TEST_GAME_BEGIN(Clock, FrameRate)
{
	void OnUpdate(f32 deltaTime) override
	{
		static u32 frameCount = 0;
		frameCount++;

		const Clock& clock = Clock::Get();

		if (clock.IsNewSecond())
		{
			ASSERT_EQ(clock.GetFrameRate(), frameCount);
			ASSERT_GE(clock.GetTotalTime(), 1.0f);
			Window::Get().Close();
		}
		else
		{
			ASSERT_LE(clock.GetTotalTime(), 1.0f);
		}
	}
}
TEST_GAME_END()
