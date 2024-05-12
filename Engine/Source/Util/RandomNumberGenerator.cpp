#include "RandomNumberGenerator.h"

#include <Core/Application.h>
#include "Internal/Asserts/ApplicationAsserts.h"
#include <cassert>
#include <chrono>

using namespace TGL;

RandomNumberGenerator::RandomNumberGenerator()
{
    const auto t = std::chrono::steady_clock::now();
    const auto millis = std::chrono::duration_cast<std::chrono::nanoseconds>(t.time_since_epoch()).count();
    m_Seed = static_cast<uint32_t>(millis);
}

RandomNumberGenerator::RandomNumberGenerator(const unsigned int seed)
    : m_Seed(seed)
{ }

bool RandomNumberGenerator::GetBool()
{
    UpdateSeed();
    return m_Seed % 2 == 0;
}

int RandomNumberGenerator::GetInt()
{
    UpdateSeed();
    return static_cast<int>(m_Seed);
}

int RandomNumberGenerator::GetInt(const int min, const int max)
{
    assert(min <= max && "The minimum value cannot be greater than the maximum value");
    
    UpdateSeed();
    return min + m_Seed % (max - min + 1);
}

unsigned int RandomNumberGenerator::GetUint()
{
    UpdateSeed();
    return m_Seed;
}

unsigned int RandomNumberGenerator::GetUint(const unsigned int min, const unsigned int max)
{
    assert(min <= max && "The minimum value cannot be greater than the maximum value");
    
    UpdateSeed();
    return min + m_Seed % (max - min + 1);
}

float RandomNumberGenerator::GetFloat()
{
    UpdateSeed();
    return m_Seed / static_cast<float>(UINT_MAX);
}

float RandomNumberGenerator::GetFloat(const float min, const float max)
{
    assert(min <= max && "The minimum value cannot be greater than the maximum value");
    
    UpdateSeed();
    return min + m_Seed / static_cast<float>(UINT_MAX) * (max - min);
}

double RandomNumberGenerator::GetDouble()
{ 
    UpdateSeed();
    return m_Seed / static_cast<double>(UINT_MAX);
}

double RandomNumberGenerator::GetDouble(const double min, const double max)
{
    assert(min <= max && "The minimum value cannot be greater than the maximum value");
    
    UpdateSeed();
    return min + m_Seed / static_cast<double>(UINT_MAX) * (max - min);
}

void RandomNumberGenerator::UpdateSeed()
{
    // Uses the PCG Hash algorithm to generate a new seed
    m_Seed = m_Seed * 747796405U + 2891336453U;
    m_Seed = ((m_Seed >> ((m_Seed >> 28u) + 4u)) ^ m_Seed) * 277803737U; // NOLINT(CppRedundantParentheses)
    m_Seed = (m_Seed >> 22u) ^ m_Seed; // NOLINT(CppRedundantParentheses)
}
