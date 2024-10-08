﻿#include "Core/Services/Public/Clock.h"

#include "Core/Application.h"
#include "Util/GameTestAbstractions.h"

using namespace TGL;

// Mock services

namespace
{
	class MockClock final : public Clock
	{
	protected:
		std::chrono::steady_clock::time_point CalculateCurrentTime() const override
		{
			return m_LastFrameTime + std::chrono::milliseconds(100);
		}
	};

	void MockServiceBuilder(ServiceCollection& collection)
	{
		collection.CreateService<MockClock>();
	}
}

// Tests

BEGIN_GAME_TEST_MOCKED(Clock, TimeProgression, MockServiceBuilder)
{
	void OnUpdate(const f32 deltaTime) override
	{
		static i32 lastFrame = 0;
		static f32 lastTime = 0.0f;

		const Clock& clock = Clock::Get();

		// Delta time
		EXPECT_GT(clock.GetDeltaTime(), 0.0f);

		// Total time
		const f32 currentTime = clock.GetTotalTime();

		EXPECT_GT(currentTime, lastTime);
		EXPECT_GE(currentTime, deltaTime);
		EXPECT_GT(currentTime, 0.0f);

		lastTime = currentTime;

		// Frame count
		const i32 currentFrame = clock.GetFrameCount();

		EXPECT_GE(currentFrame, 0);
		EXPECT_EQ(currentFrame, lastFrame + 1);

		lastFrame = currentFrame;

		// New Second
		const bool isNewSecond = clock.IsNewSecond();

		EXPECT_EQ(isNewSecond, currentTime >= 1.0f);

		if (isNewSecond)
		{
			EndTest();
		}
	}
}
END_GAME_TEST()

BEGIN_GAME_TEST_MOCKED(Clock, FrameRate, MockServiceBuilder)
{
	void OnUpdate(f32 deltaTime) override
	{
		static u32 frameCount = 0;
		frameCount++;

		const Clock& clock = Clock::Get();

		if (clock.IsNewSecond())
		{
			EXPECT_EQ(clock.GetFrameRate(), frameCount);
			EXPECT_GE(clock.GetTotalTime(), 1.0f);

			EndTest();
		}
		else
		{
			EXPECT_LE(clock.GetTotalTime(), 1.0f);
		}
	}
}
END_GAME_TEST()
