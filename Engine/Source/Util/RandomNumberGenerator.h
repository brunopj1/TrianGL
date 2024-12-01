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

		glm::ivec2 GetIVec2();
		glm::ivec2 GetIVec2(i32 min, i32 max);
		glm::ivec2 GetIVec2(const glm::ivec2& min, const glm::ivec2& max);

		glm::ivec3 GetIVec3();
		glm::ivec3 GetIVec3(i32 min, i32 max);
		glm::ivec3 GetIVec3(const glm::ivec3& min, const glm::ivec3& max);

		glm::ivec4 GetVec4();
		glm::ivec4 GetVec4(i32 min, i32 max);
		glm::ivec4 GetVec4(const glm::ivec4& min, const glm::ivec4& max);

		glm::uvec2 GetUVec2();
		glm::uvec2 GetUVec2(u32 min, u32 max);
		glm::uvec2 GetUVec2(const glm::uvec2& min, const glm::uvec2& max);

		glm::uvec3 GetUVec3();
		glm::uvec3 GetUVec3(u32 min, u32 max);
		glm::uvec3 GetUVec3(const glm::uvec3& min, const glm::uvec3& max);

		glm::uvec4 GetUVec4();
		glm::uvec4 GetUVec4(u32 min, u32 max);
		glm::uvec4 GetUVec4(const glm::uvec4& min, const glm::uvec4& max);

		glm::vec2 GetFVec2();
		glm::vec2 GetFVec2(f32 min, f32 max);
		glm::vec2 GetFVec2(const glm::vec2& min, const glm::vec2& max);

		glm::vec3 GetFVec3();
		glm::vec3 GetFVec3(f32 min, f32 max);
		glm::vec3 GetFVec3(const glm::vec3& min, const glm::vec3& max);

		glm::vec4 GetFVec4();
		glm::vec4 GetFVec4(f32 min, f32 max);
		glm::vec4 GetFVec4(const glm::vec4& min, const glm::vec4& max);

	private:
		void UpdateSeed();
	};
}
