#pragma once

#include "Core/Application.h"
#include "Game/GameMode.h"
#include "gtest/gtest.h"

// Begins a game test without mocking
#define BEGIN_GAME_TEST(test_suite_name, test_name) \
	BEGIN_GAME_TEST_INTERNAL(test_suite_name, test_name, nullptr)

// Begins a game test with mocking
#define BEGIN_GAME_TEST_MOCKED(test_suite_name, test_name, mock_services_builder) \
	BEGIN_GAME_TEST_INTERNAL(test_suite_name, test_name, mock_services_builder)

// Ends the current game test
// This macro is used because writing a semicolon directly after the test causes clang-format to screw up the formatting
#define END_GAME_TEST() ;

// Internal stuff (don't use these directly)

// This macro will create a test inside a new GameMode class
// This test will run in the GameMode's update loop
// To mock the services set the mock parameter to true and implement the [GetMockedServices() -> ServiceCollection] static method
#define BEGIN_GAME_TEST_INTERNAL(test_suite_name, test_name, mock_services_builder)                                     \
	class test_suite_name##_##test_name##_TestGameMode;                                                                 \
                                                                                                                        \
	TEST(test_suite_name, test_name)                                                                                    \
	{                                                                                                                   \
		const RunDetails runDetails = RunGameTest<test_suite_name##_##test_name##_TestGameMode>(mock_services_builder); \
                                                                                                                        \
		EXPECT_GT(runDetails.FrameCount, 0);                                                                            \
	}                                                                                                                   \
                                                                                                                        \
	class test_suite_name##_##test_name##_TestGameMode final : public TGL::TestGameMode

namespace TGL
{
	// Test GameMode class
	// This class helps ensure that the test will stop running after a fixed time
	// This class also ensures that the test will stop running if any assert fails
	class TestGameMode : public GameMode // NOLINT(CppClassCanBeFinal)
	{
	protected:
		static void EndTest()
		{
			Window::Get().Close();
		}

	protected:
		void OnLateUpdate(const f32 deltaTime) override
		{
			GameMode::OnLateUpdate(deltaTime);

			// Stop running after 5 seconds
			const Clock& clock = Clock::Get();
			if (clock.GetTotalTime() > 5.0f)
			{
				EXPECT_LT(clock.GetTotalTime(), 5.0f);
				EndTest();
				return;
			}

			// Stop running if any assert fails
			if (testing::Test::HasFailure())
			{
				EXPECT_FALSE(testing::Test::HasFailure());
				EndTest();
				return;
			}
		}
	};

	// Test runner function
	// This is used to allow running the Application with a forward declared GameMode
	template <typename T>
	RunDetails RunGameTest(const std::function<void(ServiceCollection&)>& mockServicesBuilder = nullptr)
	{
		ServiceCollection mockServiceCollection;

		if (mockServicesBuilder != nullptr)
		{
			mockServicesBuilder(mockServiceCollection);
		}

		const RunDetails runDetails = Application::Run<T>(ApplicationConfig(), mockServiceCollection);

		return runDetails;
	}

}
