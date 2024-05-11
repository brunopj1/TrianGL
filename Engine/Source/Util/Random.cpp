#include "Random.h"

#include <cassert>
#include <chrono>

using namespace TGL;

int Random::GetInt()
{
    UpdateSeed();
    return static_cast<int>(s_Seed);
}

int Random::GetInt(const int min, const int max)
{
    assert(min <= max && "The minimum value cannot be greater than the maximum value");
    UpdateSeed();
    return min + s_Seed % (max - min + 1);
}

unsigned int Random::GetUint()
{
    UpdateSeed();
    return s_Seed;
}

unsigned int Random::GetUint(const unsigned int min, const unsigned int max)
{
    assert(min <= max && "The minimum value cannot be greater than the maximum value");
    UpdateSeed();
    return min + s_Seed % (max - min + 1);
}

float Random::GetFloat()
{
    UpdateSeed();
    return s_Seed / static_cast<float>(UINT_MAX);
}

float Random::GetFloat(const float min, const float max)
{
    assert(min <= max && "The minimum value cannot be greater than the maximum value");
    UpdateSeed();
    return min + s_Seed / static_cast<float>(UINT_MAX) * (max - min);
}

double Random::GetDouble()
{
    UpdateSeed();
    return s_Seed / static_cast<double>(UINT_MAX);
}

double Random::GetDouble(const double min, const double max)
{
    assert(min <= max && "The minimum value cannot be greater than the maximum value");
    UpdateSeed();
    return min + s_Seed / static_cast<double>(UINT_MAX) * (max - min);
}

void Random::InitSeed()
{
    // Init the seed based on the current time
    const auto t = std::chrono::steady_clock::now();
    const auto millis = std::chrono::duration_cast<std::chrono::nanoseconds>(t.time_since_epoch()).count();
    s_Seed = static_cast<uint32_t>(millis);
}

void Random::UpdateSeed()
{
    // Uses the PCG Hash algorithm to generate a new seed
    s_Seed = s_Seed * 747796405U + 2891336453U;
    s_Seed = ((s_Seed >> ((s_Seed >> 28u) + 4u)) ^ s_Seed) * 277803737U; // NOLINT(CppRedundantParentheses)
    s_Seed = (s_Seed >> 22u) ^ s_Seed; // NOLINT(CppRedundantParentheses)
}
