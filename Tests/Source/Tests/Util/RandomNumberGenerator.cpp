﻿#include "Util/RandomNumberGenerator.h"

#include "gtest/gtest.h"
#include <limits>

template <typename T, u32 Size>
void AssertVectorRange(const glm::vec<Size, T>& vec, const T min, const T max)
{
	if constexpr (Size >= 1)
	{
		ASSERT_GE(vec.x, min);
		ASSERT_LE(vec.x, max);
	}
	if constexpr (Size >= 2)
	{
		ASSERT_GE(vec.y, min);
		ASSERT_LE(vec.y, max);
	}
	if constexpr (Size >= 3)
	{
		ASSERT_GE(vec.z, min);
		ASSERT_LE(vec.z, max);
	}
	if constexpr (Size >= 4)
	{
		ASSERT_GE(vec.w, min);
		ASSERT_LE(vec.w, max);
	}
}

TEST(RandomNumberGenerator, Constructors)
{
	TGL::RandomNumberGenerator rng1{}; // NOLINT(CppDeclaratorNeverUsed)
	TGL::RandomNumberGenerator rng2{12345}; // NOLINT(CppDeclaratorNeverUsed)
}

TEST(RandomNumberGenerator, SeedModified)
{
	TGL::RandomNumberGenerator rng;

	const auto seed1 = rng.GetSeed();

	rng.GetFloat();

	const auto seed2 = rng.GetSeed();

	ASSERT_NE(seed1, seed2);
}

TEST(RandomNumberGenerator, GetBool)
{
	TGL::RandomNumberGenerator rng;

	const auto v = rng.GetBool();

	ASSERT_TRUE(v == true || v == false);
}

TEST(RandomNumberGenerator, GetInt)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetInt();

	ASSERT_GE(v1, std::numeric_limits<i32>::min());
	ASSERT_LE(v1, std::numeric_limits<i32>::max());

	const auto v2 = rng.GetInt(0, 10);

	ASSERT_GE(v2, 0);
	ASSERT_LE(v2, 10);

	ASSERT_THROW(rng.GetInt(10, 0), std::invalid_argument);
}

TEST(RandomNumberGenerator, GetUint)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetUint();

	ASSERT_GE(v1, std::numeric_limits<u32>::min());
	ASSERT_LE(v1, std::numeric_limits<u32>::max());

	const auto v2 = rng.GetUint(0, 10);

	ASSERT_GE(v2, 0);
	ASSERT_LE(v2, 10);

	ASSERT_THROW(rng.GetUint(10, 0), std::invalid_argument);
}

TEST(RandomNumberGenerator, GetFloat)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetFloat();

	ASSERT_GE(v1, 0.0f);
	ASSERT_LE(v1, 1.0f);

	const auto v2 = rng.GetFloat(0.0f, 10.0f);

	ASSERT_GE(v2, 0.0f);
	ASSERT_LE(v2, 10.0f);

	ASSERT_THROW(rng.GetFloat(10.0f, 0.0f), std::invalid_argument);
}

TEST(RandomNumberGenerator, GetDouble)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetDouble();

	ASSERT_GE(v1, 0.0);
	ASSERT_LE(v1, 1.0);

	const auto v2 = rng.GetDouble(0.0, 10.0);

	ASSERT_GE(v2, 0.0);
	ASSERT_LE(v2, 10.0);

	ASSERT_THROW(rng.GetDouble(10.0, 0.0), std::invalid_argument);
}

TEST(RandomNumberGenerator, GetInt2)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetInt2();
	AssertVectorRange(v1, std::numeric_limits<i32>::min(), std::numeric_limits<i32>::max());

	const glm::vec<2, int> v2 = rng.GetInt2(0, 10);
	AssertVectorRange(v2, 0, 10);

	const auto v3 = rng.GetInt2({0, 0}, {10, 10});
	AssertVectorRange(v3, 0, 10);

	ASSERT_THROW(rng.GetInt2(10, 0), std::invalid_argument);
	ASSERT_THROW(rng.GetInt2({10, 10}, {0, 0}), std::invalid_argument);
}

TEST(RandomNumberGenerator, GetInt3)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetInt3();
	AssertVectorRange(v1, std::numeric_limits<i32>::min(), std::numeric_limits<i32>::max());

	const auto v2 = rng.GetInt3(0, 10);
	AssertVectorRange(v2, 0, 10);

	const auto v3 = rng.GetInt3({0, 0, 0}, {10, 10, 10});
	AssertVectorRange(v3, 0, 10);

	ASSERT_THROW(rng.GetInt3(10, 0), std::invalid_argument);
	ASSERT_THROW(rng.GetInt3({10, 10, 10}, {0, 0, 0}), std::invalid_argument);
}

TEST(RandomNumberGenerator, GetInt4)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetInt4();
	AssertVectorRange(v1, std::numeric_limits<i32>::min(), std::numeric_limits<i32>::max());

	const auto v2 = rng.GetInt4(0, 10);
	AssertVectorRange(v2, 0, 10);

	const auto v3 = rng.GetInt4({0, 0, 0, 0}, {10, 10, 10, 10});
	AssertVectorRange(v3, 0, 10);

	ASSERT_THROW(rng.GetInt4(10, 0), std::invalid_argument);
	ASSERT_THROW(rng.GetInt4({10, 10, 10, 10}, {0, 0, 0, 0}), std::invalid_argument);
}

TEST(RandomNumberGenerator, GetUint2)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetUint2();
	AssertVectorRange(v1, std::numeric_limits<u32>::min(), std::numeric_limits<u32>::max());

	const auto v2 = rng.GetUint2(0, 10);
	AssertVectorRange(v2, 0u, 10u);

	const auto v3 = rng.GetUint2({0, 0}, {10, 10});
	AssertVectorRange(v3, 0u, 10u);

	ASSERT_THROW(rng.GetUint2(10, 0), std::invalid_argument);
	ASSERT_THROW(rng.GetUint2({10, 10}, {0, 0}), std::invalid_argument);
}

TEST(RandomNumberGenerator, GetUint3)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetUint3();
	AssertVectorRange(v1, std::numeric_limits<u32>::min(), std::numeric_limits<u32>::max());

	const auto v2 = rng.GetUint3(0, 10);
	AssertVectorRange(v2, 0u, 10u);

	const auto v3 = rng.GetUint3({0, 0, 0}, {10, 10, 10});
	AssertVectorRange(v3, 0u, 10u);

	ASSERT_THROW(rng.GetUint3(10, 0), std::invalid_argument);
	ASSERT_THROW(rng.GetUint3({10, 10, 10}, {0, 0, 0}), std::invalid_argument);
}

TEST(RandomNumberGenerator, GetUint4)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetUint4();
	AssertVectorRange(v1, std::numeric_limits<u32>::min(), std::numeric_limits<u32>::max());

	const auto v2 = rng.GetUint4(0, 10);
	AssertVectorRange(v2, 0u, 10u);

	const auto v3 = rng.GetUint4({0, 0, 0, 0}, {10, 10, 10, 10});
	AssertVectorRange(v3, 0u, 10u);

	ASSERT_THROW(rng.GetUint4(10, 0), std::invalid_argument);
	ASSERT_THROW(rng.GetUint4({10, 10, 10, 10}, {0, 0, 0, 0}), std::invalid_argument);
}

TEST(RandomNumberGenerator, GetFloat2)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetFloat2();
	AssertVectorRange(v1, 0.0f, 1.0f);

	const auto v2 = rng.GetFloat2(0.0f, 10.0f);
	AssertVectorRange(v2, 0.0f, 10.0f);

	const auto v3 = rng.GetFloat2({0.0f, 0.0f}, {10.0f, 10.0f});
	AssertVectorRange(v3, 0.0f, 10.0f);

	ASSERT_THROW(rng.GetFloat2(10.0f, 0.0f), std::invalid_argument);
	ASSERT_THROW(rng.GetFloat2({10.0f, 10.0f}, {0.0f, 0.0f}), std::invalid_argument);
}

TEST(RandomNumberGenerator, GetFloat3)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetFloat3();
	AssertVectorRange(v1, 0.0f, 1.0f);

	const auto v2 = rng.GetFloat3(0.0f, 10.0f);
	AssertVectorRange(v2, 0.0f, 10.0f);

	const auto v3 = rng.GetFloat3({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 10.0f});
	AssertVectorRange(v3, 0.0f, 10.0f);

	ASSERT_THROW(rng.GetFloat3(10.0f, 0.0f), std::invalid_argument);
	ASSERT_THROW(rng.GetFloat3({10.0f, 10.0f, 10.0f}, {0.0f, 0.0f, 0.0f}), std::invalid_argument);
}

TEST(RandomNumberGenerator, GetFloat4)
{
	TGL::RandomNumberGenerator rng;

	const auto v1 = rng.GetFloat4();
	AssertVectorRange(v1, 0.0f, 1.0f);

	const auto v2 = rng.GetFloat4(0.0f, 10.0f);
	AssertVectorRange(v2, 0.0f, 10.0f);

	const auto v3 = rng.GetFloat4({0.0f, 0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 10.0f, 10.0f});
	AssertVectorRange(v3, 0.0f, 10.0f);

	ASSERT_THROW(rng.GetFloat4(10.0f, 0.0f), std::invalid_argument);
	ASSERT_THROW(rng.GetFloat4({10.0f, 10.0f, 10.0f, 10.0f}, {0.0f, 0.0f, 0.0f, 0.0f}), std::invalid_argument);
}
