#include "gtest/gtest.h"

namespace FactorialTests
{
	int Factorial(int n)
	{
		return n <= 1 ? 1 : Factorial(n - 1) * n;
	}

	TEST(FactorialTest, HandlesPositiveInput)
	{
		EXPECT_EQ(Factorial(1), 1);
		EXPECT_EQ(Factorial(2), 2);
		EXPECT_EQ(Factorial(3), 6);
		EXPECT_EQ(Factorial(8), 40320);
	}

	TEST(FactorialTest, HandlesNegativeInput)
	{
		EXPECT_EQ(Factorial(-1), 1);
		EXPECT_EQ(Factorial(-2), 1);
		EXPECT_EQ(Factorial(-3), 1);
		EXPECT_EQ(Factorial(-8), 1);
	}

	TEST(FactorialTest, HandlesZeroInput)
	{
		EXPECT_EQ(Factorial(0), 1);
	}
}