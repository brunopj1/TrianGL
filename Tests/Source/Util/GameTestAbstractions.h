#pragma once

#include "Core/Application.h"
#include "Game/GameMode.h"
#include "gtest/gtest.h"

// This macro will create a test inside a new GameMode class
// This test will run in the GameMode's update loop
#define TEST_GAME_BEGIN(test_suite_name, test_name)                                   \
	static_assert(sizeof(#test_suite_name) > 1, "test_suite_name must not be empty"); \
	static_assert(sizeof(#test_name) > 1, "test_name must not be empty");             \
                                                                                      \
	class test_suite_name##_##test_name##_GameMode;                                   \
                                                                                      \
	TEST(test_suite_name, test_name)                                                  \
	{                                                                                 \
		const f32 duration = RunGameTest<test_suite_name##_##test_name##_GameMode>(); \
                                                                                      \
		ASSERT_GT(duration, 0.0f);                                                    \
	}                                                                                 \
                                                                                      \
	class test_suite_name##_##test_name##_GameMode final : public TGL::TestGameMode

// This macro will end the current game test scope
// This macro is used because writing a semicolon directly after the test causes clang-format to screw up the formatting
#define TEST_GAME_END() ;

namespace TGL
{
	// Test GameMode class
	// This class helps ensure that the test will stop running after a fixed time
	// This class also ensures that the test will stop running if any assert fails
	class TestGameMode : public GameMode // NOLINT(CppClassCanBeFinal)
	{
	protected:
		void OnLateUpdate(f32 deltaTime) override
		{
			// Stop running after 5 seconds
			const Clock& clock = Clock::Get();
			if (clock.GetTotalTime() > 5.0f)
			{
				Window::Get().Close();
				ASSERT_LT(clock.GetTotalTime(), 5.0f);
			}

			// Stop running if any assert fails
			if (testing::Test::HasFailure())
			{
				Window::Get().Close();
				ASSERT_FALSE(testing::Test::HasFailure());
			}
		}
	};

	// Test runner function
	// This is used to allow running the Application with a forward declared GameMode
	template <typename T>
	f32 RunGameTest()
	{
		return Application::Run<T>(ApplicationConfig(), ServiceCollection());
	}

}
