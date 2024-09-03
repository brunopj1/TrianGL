#pragma once

#include "gtest/gtest.h"

// Test macros

// Will create a test inside a new GameMode class
// This test will run in the GameMode's update loop
#define TEST_GAME_BEGIN(test_suite_name, test_name)                                   \
	static_assert(sizeof(#test_suite_name) > 1, "test_suite_name must not be empty"); \
	static_assert(sizeof(#test_name) > 1, "test_name must not be empty");             \
                                                                                      \
	class test_suite_name##_##test_name##_GameMode;                                   \
                                                                                      \
	TEST(test_suite_name, test_name)                                                  \
	{                                                                                 \
		RunGameTest<test_suite_name##_##test_name##_GameMode>();                      \
	}                                                                                 \
                                                                                      \
	class test_suite_name##_##test_name##_GameMode final : public GameMode

// Will end the current game test
// This macro is used because writing a semicolon directly after the test causes clang-format to screw up the formatting
#define TEST_GAME_END ;

// Test runner function

template <typename T>
void RunGameTest()
{
	// This is used to allow running the Application with a forward declared GameMode
	TGL::Application::Run<T>({}, {});
}
