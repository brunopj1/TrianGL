#pragma once

#include "Core/DataTypes.h"
#include <glm/glm.hpp>

namespace TGL
{
	class RandomNumberGenerator
	{
	private:
		friend class Application;

	private:
		u32 m_Seed;

	public:
		RandomNumberGenerator(); // Will use a random seed
		RandomNumberGenerator(u32 seed);
		~RandomNumberGenerator() = default;

	public:
		u32 GetSeed() const;

	public:
		bool GetBool();

		i32 GetInt();
		i32 GetInt(i32 min, i32 max);

		u32 GetUint();
		u32 GetUint(u32 min, u32 max);

		f32 GetFloat();
		f32 GetFloat(f32 min, f32 max);

		f64 GetDouble();
		f64 GetDouble(f64 min, f64 max);

		glm::ivec2 GetInt2();
		glm::ivec2 GetInt2(i32 min, i32 max);
		glm::ivec2 GetInt2(const glm::ivec2& min, const glm::ivec2& max);

		glm::ivec3 GetInt3();
		glm::ivec3 GetInt3(i32 min, i32 max);
		glm::ivec3 GetInt3(const glm::ivec3& min, const glm::ivec3& max);

		glm::ivec4 GetInt4();
		glm::ivec4 GetInt4(i32 min, i32 max);
		glm::ivec4 GetInt4(const glm::ivec4& min, const glm::ivec4& max);

		glm::uvec2 GetUint2();
		glm::uvec2 GetUint2(u32 min, u32 max);
		glm::uvec2 GetUint2(const glm::uvec2& min, const glm::uvec2& max);

		glm::uvec3 GetUint3();
		glm::uvec3 GetUint3(u32 min, u32 max);
		glm::uvec3 GetUint3(const glm::uvec3& min, const glm::uvec3& max);

		glm::uvec4 GetUint4();
		glm::uvec4 GetUint4(u32 min, u32 max);
		glm::uvec4 GetUint4(const glm::uvec4& min, const glm::uvec4& max);

		glm::vec2 GetFloat2();
		glm::vec2 GetFloat2(f32 min, f32 max);
		glm::vec2 GetFloat2(const glm::vec2& min, const glm::vec2& max);

		glm::vec3 GetFloat3();
		glm::vec3 GetFloat3(f32 min, f32 max);
		glm::vec3 GetFloat3(const glm::vec3& min, const glm::vec3& max);

		glm::vec4 GetFloat4();
		glm::vec4 GetFloat4(f32 min, f32 max);
		glm::vec4 GetFloat4(const glm::vec4& min, const glm::vec4& max);

	private:
		void UpdateSeed();
	};
}
