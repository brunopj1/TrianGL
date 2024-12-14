#include <gtest/gtest.h>
#include <iostream>

#ifndef TESTING
static_assert(false, "The unit tests are only available in the Testing configuration.");
#endif

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	std::cout << "Running tests..." << std::endl; // NOLINT(performance-avoid-endl)
	return RUN_ALL_TESTS();
}
