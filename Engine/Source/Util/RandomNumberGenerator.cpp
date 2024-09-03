#include <Core/Application.h>
#include <Util/RandomNumberGenerator.h>
#include <chrono>

using namespace TGL;

RandomNumberGenerator::RandomNumberGenerator()
{
	const auto t = std::chrono::steady_clock::now();
	const auto millis = std::chrono::duration_cast<std::chrono::nanoseconds>(t.time_since_epoch()).count();
	m_Seed = static_cast<u32>(millis);
}

RandomNumberGenerator::RandomNumberGenerator(const u32 seed)
	: m_Seed(seed) {}

u32 RandomNumberGenerator::GetSeed() const
{
	return m_Seed;
}

bool RandomNumberGenerator::GetBool()
{
	UpdateSeed();
	return m_Seed % 2 == 0;
}

i32 RandomNumberGenerator::GetInt()
{
	UpdateSeed();
	return static_cast<i32>(m_Seed);
}

i32 RandomNumberGenerator::GetInt(const i32 min, const i32 max)
{
	if (max < min)
	{
		throw std::invalid_argument("The minimum value cannot be greater than the maximum value");
	}

	UpdateSeed();
	return min + m_Seed % (max - min + 1);
}

u32 RandomNumberGenerator::GetUint()
{
	UpdateSeed();
	return m_Seed;
}

u32 RandomNumberGenerator::GetUint(const u32 min, const u32 max)
{
	if (max < min)
	{
		throw std::invalid_argument("The minimum value cannot be greater than the maximum value");
	}

	UpdateSeed();
	return min + m_Seed % (max - min + 1);
}

f32 RandomNumberGenerator::GetFloat()
{
	UpdateSeed();
	return m_Seed / static_cast<f32>(UINT_MAX);
}

f32 RandomNumberGenerator::GetFloat(const f32 min, const f32 max)
{
	if (max < min)
	{
		throw std::invalid_argument("The minimum value cannot be greater than the maximum value");
	}

	UpdateSeed();
	return min + m_Seed / static_cast<f32>(UINT_MAX) * (max - min);
}

f64 RandomNumberGenerator::GetDouble()
{
	UpdateSeed();
	return m_Seed / static_cast<f64>(UINT_MAX);
}

f64 RandomNumberGenerator::GetDouble(const f64 min, const f64 max)
{
	if (max < min)
	{
		throw std::invalid_argument("The minimum value cannot be greater than the maximum value");
	}

	UpdateSeed();
	return min + m_Seed / static_cast<f64>(UINT_MAX) * (max - min);
}

glm::ivec2 RandomNumberGenerator::GetInt2()
{
	return {GetInt(), GetInt()};
}

glm::ivec2 RandomNumberGenerator::GetInt2(const i32 min, const i32 max)
{
	return {GetInt(min, max), GetInt(min, max)};
}

glm::ivec2 RandomNumberGenerator::GetInt2(const glm::ivec2& min, const glm::ivec2& max)
{
	return {GetInt(min.x, max.x), GetInt(min.y, max.y)};
}

glm::ivec3 RandomNumberGenerator::GetInt3()
{
	return {GetInt(), GetInt(), GetInt()};
}

glm::ivec3 RandomNumberGenerator::GetInt3(const i32 min, const i32 max)
{
	return {GetInt(min, max), GetInt(min, max), GetInt(min, max)};
}

glm::ivec3 RandomNumberGenerator::GetInt3(const glm::ivec3& min, const glm::ivec3& max)
{
	return {GetInt(min.x, max.x), GetInt(min.y, max.y), GetInt(min.z, max.z)};
}

glm::ivec4 RandomNumberGenerator::GetInt4()
{
	return {GetInt(), GetInt(), GetInt(), GetInt()};
}

glm::ivec4 RandomNumberGenerator::GetInt4(const i32 min, const i32 max)
{
	return {GetInt(min, max), GetInt(min, max), GetInt(min, max), GetInt(min, max)};
}

glm::ivec4 RandomNumberGenerator::GetInt4(const glm::ivec4& min, const glm::ivec4& max)
{
	return {GetInt(min.x, max.x), GetInt(min.y, max.y), GetInt(min.z, max.z), GetInt(min.w, max.w)};
}

glm::uvec2 RandomNumberGenerator::GetUint2()
{
	return {GetUint(), GetUint()};
}

glm::uvec2 RandomNumberGenerator::GetUint2(const u32 min, const u32 max)
{
	return {GetUint(min, max), GetUint(min, max)};
}

glm::uvec2 RandomNumberGenerator::GetUint2(const glm::uvec2& min, const glm::uvec2& max)
{
	return {GetUint(min.x, max.x), GetUint(min.y, max.y)};
}

glm::uvec3 RandomNumberGenerator::GetUint3()
{
	return {GetUint(), GetUint(), GetUint()};
}

glm::uvec3 RandomNumberGenerator::GetUint3(const u32 min, const u32 max)
{
	return {GetUint(min, max), GetUint(min, max), GetUint(min, max)};
}

glm::uvec3 RandomNumberGenerator::GetUint3(const glm::uvec3& min, const glm::uvec3& max)
{
	return {GetUint(min.x, max.x), GetUint(min.y, max.y), GetUint(min.z, max.z)};
}

glm::uvec4 RandomNumberGenerator::GetUint4()
{
	return {GetUint(), GetUint(), GetUint(), GetUint()};
}

glm::uvec4 RandomNumberGenerator::GetUint4(const u32 min, const u32 max)
{
	return {GetUint(min, max), GetUint(min, max), GetUint(min, max), GetUint(min, max)};
}

glm::uvec4 RandomNumberGenerator::GetUint4(const glm::uvec4& min, const glm::uvec4& max)
{
	return {GetUint(min.x, max.x), GetUint(min.y, max.y), GetUint(min.z, max.z), GetUint(min.w, max.w)};
}

glm::vec2 RandomNumberGenerator::GetFloat2()
{
	return {GetFloat(), GetFloat()};
}

glm::vec2 RandomNumberGenerator::GetFloat2(const f32 min, const f32 max)
{
	return {GetFloat(min, max), GetFloat(min, max)};
}

glm::vec2 RandomNumberGenerator::GetFloat2(const glm::vec2& min, const glm::vec2& max)
{
	return {GetFloat(min.x, max.x), GetFloat(min.y, max.y)};
}

glm::vec3 RandomNumberGenerator::GetFloat3()
{
	return {GetFloat(), GetFloat(), GetFloat()};
}

glm::vec3 RandomNumberGenerator::GetFloat3(const f32 min, const f32 max)
{
	return {GetFloat(min, max), GetFloat(min, max), GetFloat(min, max)};
}

glm::vec3 RandomNumberGenerator::GetFloat3(const glm::vec3& min, const glm::vec3& max)
{
	return {GetFloat(min.x, max.x), GetFloat(min.y, max.y), GetFloat(min.z, max.z)};
}

glm::vec4 RandomNumberGenerator::GetFloat4()
{
	return {GetFloat(), GetFloat(), GetFloat(), GetFloat()};
}

glm::vec4 RandomNumberGenerator::GetFloat4(const f32 min, const f32 max)
{
	return {GetFloat(min, max), GetFloat(min, max), GetFloat(min, max), GetFloat(min, max)};
}

glm::vec4 RandomNumberGenerator::GetFloat4(const glm::vec4& min, const glm::vec4& max)
{
	return {GetFloat(min.x, max.x), GetFloat(min.y, max.y), GetFloat(min.z, max.z), GetFloat(min.w, max.w)};
}

void RandomNumberGenerator::UpdateSeed()
{
	// Uses the PCG Hash algorithm to generate a new seed
	m_Seed = m_Seed * 747796405U + 2891336453U;
	m_Seed = ((m_Seed >> ((m_Seed >> 28u) + 4u)) ^ m_Seed) * 277803737U; // NOLINT(CppRedundantParentheses)
	m_Seed = (m_Seed >> 22u) ^ m_Seed; // NOLINT(CppRedundantParentheses)
}
