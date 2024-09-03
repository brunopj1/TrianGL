#include "Core/Services/Clock.h"

#include "Core/Application.h"
#include "Core/Services/Window.h"
#include "Game/GameMode.h"
#include "Util/TestMacros.h"

using namespace TGL;

// TODO fix clang-format for the TEST_GAME macro

TEST_GAME(Clock, TimeProgression,
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

        if (isNewSecond) Window::Get().Close();
	}
})

TEST_GAME(Clock, FrameRate,
{
    void OnUpdate(f32 deltaTime) override
    {
        static u32 frameCount = 0;
        frameCount++;

        const Clock& clock = Clock::Get();

        if (clock.IsNewSecond())
        {
			ASSERT_EQ(clock.GetFrameRate(), frameCount);
			Window::Get().Close();
			
        }
	}
})
