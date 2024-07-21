#include "Util/RandomNumberGenerator.h"
#include <limits>

#include "gtest/gtest.h"

TGL::RandomNumberGenerator g_Rng;

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
    TGL::RandomNumberGenerator rng1{}; // NOLINT
    TGL::RandomNumberGenerator rng2{12345}; // NOLINT
}

TEST(RandomNumberGenerator, SeedModified)
{
    const auto seed1 = g_Rng.GetSeed();

    g_Rng.GetFloat();

    const auto seed2 = g_Rng.GetSeed();

    ASSERT_NE(seed1, seed2);
}

TEST(RandomNumberGenerator, GetBool)
{
    const auto v = g_Rng.GetBool();

    ASSERT_TRUE(v == true || v == false);
}

TEST(RandomNumberGenerator, GetInt)
{
    const auto v1 = g_Rng.GetInt();

    ASSERT_GE(v1, std::numeric_limits<i32>::min());
    ASSERT_LE(v1, std::numeric_limits<i32>::max());

    const auto v2 = g_Rng.GetInt(0, 10);

    ASSERT_GE(v2, 0);
    ASSERT_LE(v2, 10);

    ASSERT_DEATH(g_Rng.GetInt(10, 0), "");
}

TEST(RandomNumberGenerator, GetUint)
{
    const auto v1 = g_Rng.GetUint();

    ASSERT_GE(v1, std::numeric_limits<u32>::min());
    ASSERT_LE(v1, std::numeric_limits<u32>::max());

    const auto v2 = g_Rng.GetUint(0, 10);

    ASSERT_GE(v2, 0);
    ASSERT_LE(v2, 10);

    ASSERT_DEATH(g_Rng.GetUint(10, 0), "");
}

TEST(RandomNumberGenerator, GetFloat)
{
    const auto v1 = g_Rng.GetFloat();

    ASSERT_GE(v1, 0.0f);
    ASSERT_LE(v1, 1.0f);

    const auto v2 = g_Rng.GetFloat(0.0f, 10.0f);

    ASSERT_GE(v2, 0.0f);
    ASSERT_LE(v2, 10.0f);

    ASSERT_DEATH(g_Rng.GetFloat(10.0f, 0.0f), "");
}

TEST(RandomNumberGenerator, GetDouble)
{
    const auto v1 = g_Rng.GetDouble();

    ASSERT_GE(v1, 0.0);
    ASSERT_LE(v1, 1.0);

    const auto v2 = g_Rng.GetDouble(0.0, 10.0);

    ASSERT_GE(v2, 0.0);
    ASSERT_LE(v2, 10.0);

    ASSERT_DEATH(g_Rng.GetDouble(10.0, 0.0), "");
}

TEST(RandomNumberGenerator, GetInt2)
{
    const auto v1 = g_Rng.GetInt2();
    AssertVectorRange(v1, std::numeric_limits<i32>::min(), std::numeric_limits<i32>::max());

    const glm::vec<2, int> v2 = g_Rng.GetInt2(0, 10);
    AssertVectorRange(v2, 0, 10);

    const auto v3 = g_Rng.GetInt2({0, 0}, {10, 10});
    AssertVectorRange(v3, 0, 10);

    ASSERT_DEATH(g_Rng.GetInt2(10, 0), "");
    ASSERT_DEATH(g_Rng.GetInt2({10, 10}, {0, 0}), "");
}

TEST(RandomNumberGenerator, GetInt3)
{
    const auto v1 = g_Rng.GetInt3();
    AssertVectorRange(v1, std::numeric_limits<i32>::min(), std::numeric_limits<i32>::max());

    const auto v2 = g_Rng.GetInt3(0, 10);
    AssertVectorRange(v2, 0, 10);

    const auto v3 = g_Rng.GetInt3({0, 0, 0}, {10, 10, 10});
    AssertVectorRange(v3, 0, 10);

    ASSERT_DEATH(g_Rng.GetInt3(10, 0), "");
    ASSERT_DEATH(g_Rng.GetInt3({10, 10, 10}, {0, 0, 0}), "");
}

TEST(RandomNumberGenerator, GetInt4)
{
    const auto v1 = g_Rng.GetInt4();
    AssertVectorRange(v1, std::numeric_limits<i32>::min(), std::numeric_limits<i32>::max());

    const auto v2 = g_Rng.GetInt4(0, 10);
    AssertVectorRange(v2, 0, 10);

    const auto v3 = g_Rng.GetInt4({0, 0, 0, 0}, {10, 10, 10, 10});
    AssertVectorRange(v3, 0, 10);

    ASSERT_DEATH(g_Rng.GetInt4(10, 0), "");
    ASSERT_DEATH(g_Rng.GetInt4({10, 10, 10, 10}, {0, 0, 0, 0}), "");
}

TEST(RandomNumberGenerator, GetUint2)
{
    const auto v1 = g_Rng.GetUint2();
    AssertVectorRange(v1, std::numeric_limits<u32>::min(), std::numeric_limits<u32>::max());

    const auto v2 = g_Rng.GetUint2(0, 10);
    AssertVectorRange(v2, 0u, 10u);

    const auto v3 = g_Rng.GetUint2({0, 0}, {10, 10});
    AssertVectorRange(v3, 0u, 10u);

    ASSERT_DEATH(g_Rng.GetUint2(10, 0), "");
    ASSERT_DEATH(g_Rng.GetUint2({10, 10}, {0, 0}), "");
}

TEST(RandomNumberGenerator, GetUint3)
{
    const auto v1 = g_Rng.GetUint3();
    AssertVectorRange(v1, std::numeric_limits<u32>::min(), std::numeric_limits<u32>::max());

    const auto v2 = g_Rng.GetUint3(0, 10);
    AssertVectorRange(v2, 0u, 10u);

    const auto v3 = g_Rng.GetUint3({0, 0, 0}, {10, 10, 10});
    AssertVectorRange(v3, 0u, 10u);

    ASSERT_DEATH(g_Rng.GetUint3(10, 0), "");
    ASSERT_DEATH(g_Rng.GetUint3({10, 10, 10}, {0, 0, 0}), "");
}

TEST(RandomNumberGenerator, GetUint4)
{
    const auto v1 = g_Rng.GetUint4();
    AssertVectorRange(v1, std::numeric_limits<u32>::min(), std::numeric_limits<u32>::max());

    const auto v2 = g_Rng.GetUint4(0, 10);
    AssertVectorRange(v2, 0u, 10u);

    const auto v3 = g_Rng.GetUint4({0, 0, 0, 0}, {10, 10, 10, 10});
    AssertVectorRange(v3, 0u, 10u);

    ASSERT_DEATH(g_Rng.GetUint4(10, 0), "");
    ASSERT_DEATH(g_Rng.GetUint4({10, 10, 10, 10}, {0, 0, 0, 0}), "");
}

TEST(RandomNumberGenerator, GetFloat2)
{
    const auto v1 = g_Rng.GetFloat2();
    AssertVectorRange(v1, 0.0f, 1.0f);

    const auto v2 = g_Rng.GetFloat2(0.0f, 10.0f);
    AssertVectorRange(v2, 0.0f, 10.0f);

    const auto v3 = g_Rng.GetFloat2({0.0f, 0.0f}, {10.0f, 10.0f});
    AssertVectorRange(v3, 0.0f, 10.0f);

    ASSERT_DEATH(g_Rng.GetFloat2(10.0f, 0.0f), "");
    ASSERT_DEATH(g_Rng.GetFloat2({10.0f, 10.0f}, {0.0f, 0.0f}), "");
}

TEST(RandomNumberGenerator, GetFloat3)
{
    const auto v1 = g_Rng.GetFloat3();
    AssertVectorRange(v1, 0.0f, 1.0f);

    const auto v2 = g_Rng.GetFloat3(0.0f, 10.0f);
    AssertVectorRange(v2, 0.0f, 10.0f);

    const auto v3 = g_Rng.GetFloat3({0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 10.0f});
    AssertVectorRange(v3, 0.0f, 10.0f);

    ASSERT_DEATH(g_Rng.GetFloat3(10.0f, 0.0f), "");
    ASSERT_DEATH(g_Rng.GetFloat3({10.0f, 10.0f, 10.0f}, {0.0f, 0.0f, 0.0f}), "");
}

TEST(RandomNumberGenerator, GetFloat4)
{
    const auto v1 = g_Rng.GetFloat4();
    AssertVectorRange(v1, 0.0f, 1.0f);

    const auto v2 = g_Rng.GetFloat4(0.0f, 10.0f);
    AssertVectorRange(v2, 0.0f, 10.0f);

    const auto v3 = g_Rng.GetFloat4({0.0f, 0.0f, 0.0f, 0.0f}, {10.0f, 10.0f, 10.0f, 10.0f});
    AssertVectorRange(v3, 0.0f, 10.0f);

    ASSERT_DEATH(g_Rng.GetFloat4(10.0f, 0.0f), "");
    ASSERT_DEATH(g_Rng.GetFloat4({10.0f, 10.0f, 10.0f, 10.0f}, {0.0f, 0.0f, 0.0f, 0.0f}), "");
}
