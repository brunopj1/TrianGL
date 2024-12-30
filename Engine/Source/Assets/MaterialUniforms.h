#pragma once

#include "Assets/Internal/ShaderInfo.h"
#include "Core/Internal/Macros/ClassMacros.h"
#include <Assets/Texture.h> // Required for SharedPtr<Sprite>
#include <Memory/SharedPtr.h>
#include <glm/glm.hpp>
#include <string>

namespace TGL
{
	// Helper enum
	enum class OnInvalidUniform : u8
	{
		Create,
		Ignore,
		Throw
	};

	// Forward declaration
	class Shader;

	// Base class
	class MaterialUniform
	{
	private:
		friend class AssetManager;
		friend class Material;

	protected:
		i32 m_Location;

	protected:
		MaterialUniform(const Shader* shader, const std::vector<MaterialUniform*>& existingUniforms, const std::string& name, ShaderDataType dataType);
		virtual ~MaterialUniform();

	public:
		DELETE_COPY_AND_MOVE_CONSTRUCTORS(MaterialUniform);

	private:
		virtual bool IsValid() const;
		void Bind() const;
		virtual void BindInternal() const = 0;
	};

	// Template class

	template <typename T, ShaderDataType DataType>
	class MaterialUniformImpl final : public MaterialUniform
	{
	public:
		T Value;

	public:
		MaterialUniformImpl(const Shader* shader, const std::vector<MaterialUniform*>& existingUniforms, const std::string& name)
			: MaterialUniform(shader, existingUniforms, name, DataType), Value() {}

		~MaterialUniformImpl() override = default;

	private:
		void BindInternal() const override;
	};

	// Common implementations

	using IntUniform = MaterialUniformImpl<i32, ShaderDataType::INT>;

	using UintUniform = MaterialUniformImpl<u32, ShaderDataType::UINT>;

	using FloatUniform = MaterialUniformImpl<f32, ShaderDataType::FLOAT>;

	using IVec2Uniform = MaterialUniformImpl<glm::ivec2, ShaderDataType::IVEC2>;

	using IVec3Uniform = MaterialUniformImpl<glm::ivec3, ShaderDataType::IVEC3>;

	using IVec4Uniform = MaterialUniformImpl<glm::ivec4, ShaderDataType::IVEC4>;

	using UVec2Uniform = MaterialUniformImpl<glm::uvec2, ShaderDataType::UVEC2>;

	using UVec3Uniform = MaterialUniformImpl<glm::uvec3, ShaderDataType::UVEC3>;

	using UVec4Uniform = MaterialUniformImpl<glm::uvec4, ShaderDataType::UVEC4>;

	using FVec2Uniform = MaterialUniformImpl<glm::vec2, ShaderDataType::FVEC2>;

	using FVec3Uniform = MaterialUniformImpl<glm::vec3, ShaderDataType::FVEC3>;

	using FVec4Uniform = MaterialUniformImpl<glm::vec4, ShaderDataType::FVEC4>;

	using Mat2Uniform = MaterialUniformImpl<glm::mat2, ShaderDataType::MAT2>;

	using Mat3Uniform = MaterialUniformImpl<glm::mat3, ShaderDataType::MAT3>;

	using Mat4Uniform = MaterialUniformImpl<glm::mat4, ShaderDataType::MAT4>;

	// Sprite uniform

	class SpriteUniform final : public MaterialUniform
	{
	private:
		friend class AssetManager;

	private:
		i32 m_MatrixLocation;
		i32 m_ResolutionLocation;
		u8 m_Slot = 0;

	public:
		SharedPtr<Sprite> Value;

	public:
		SpriteUniform(const Shader* shader, const std::vector<MaterialUniform*>& existingUniforms, const std::string& name);
		~SpriteUniform() override = default;

	public:
		bool HasValue() const;

	private:
		bool IsValid() const override;
		void BindInternal() const override;
	};
}
