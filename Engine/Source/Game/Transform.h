#pragma once

#include "Core/DataTypes.h"
#include "Core/Internal/Concepts/ParticleSystemConcepts.h"
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

namespace TGL
{
	class Transform
	{
	private:
		friend class SpriteRenderer;

		template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
		friend class ParticleSystem;

	private:
		glm::vec2 m_Position = {0.0f, 0.0f};
		f32 m_Rotation = 0.0f;
		glm::vec2 m_Scale = {1.0f, 1.0f};

		glm::mat4 m_TransformMatrix = glm::mat4(1.0f);

		bool m_WasModified = false;

	public:
		Transform() = default;
		~Transform() = default;

	public:
		glm::vec2 GetPosition() const;
		f32 GetRotationRad() const;
		f32 GetRotationDeg() const;
		glm::vec2 GetScale() const;

	public:
		void SetPosition(const glm::vec2& newPosition);
		void SetRotationRad(f32 newRotation);
		void SetRotationDeg(f32 newRotation);
		void SetScale(const glm::vec2& newScale);
		void SetScale(f32 newScale);

	public:
		void TranslateBy(const glm::vec2& translation);
		void RotateByRad(f32 rotation);
		void RotateByDeg(f32 rotation);
		void ScaleBy(const glm::vec2& scale);
		void ScaleBy(f32 scale);

	private:
		glm::mat4 GetTransformMatrix();
	};
}
