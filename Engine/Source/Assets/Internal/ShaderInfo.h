#pragma once

#include "Core/DataTypes.h"
#include <string>

namespace TGL
{
	// NOLINTBEGIN(CppInconsistentNaming)
	// clang-format off

	enum class ShaderDataType : u16
	{
		INT       = 0x1404, // GL_INT
		UINT      = 0x1405, // GL_UNSIGNED_INT
		FLOAT     = 0x1406, // GL_FLOAT
		IVEC2     = 0x8B53, // GL_INT_VEC2
		IVEC3     = 0x8B54, // GL_INT_VEC3
		IVEC4     = 0x8B55, // GL_INT_VEC4
		UVEC2     = 0x8DC6, // GL_UNSIGNED_INT_VEC2
		UVEC3     = 0x8DC7, // GL_UNSIGNED_INT_VEC3
		UVEC4     = 0x8DC8, // GL_UNSIGNED_INT_VEC4
		FVEC2     = 0x8B50, // GL_FLOAT_VEC2
		FVEC3     = 0x8B51, // GL_FLOAT_VEC3
		FVEC4     = 0x8B52, // GL_FLOAT_VEC4
		MAT2      = 0x8B5A, // GL_FLOAT_MAT2
		MAT3      = 0x8B5B, // GL_FLOAT_MAT3
		MAT4      = 0x8B5C, // GL_FLOAT_MAT4
		MAT2X3    = 0x8B65, // GL_FLOAT_MAT2x3
		MAT2X4    = 0x8B66, // GL_FLOAT_MAT2x4
		MAT3X2    = 0x8B67, // GL_FLOAT_MAT3x2
		MAT3X4    = 0x8B68, // GL_FLOAT_MAT3x4
		MAT4X2    = 0x8B69, // GL_FLOAT_MAT4x2
		MAT4X3    = 0x8B6A, // GL_FLOAT_MAT4x3
		SAMPLER2D = 0x8B5E, // GL_SAMPLER_2D
		INVALID   = 0 // Used when an attribute or uniform does not exist
	};

	// clang-format on
	// NOLINTEND(CppInconsistentNaming)

	struct ShaderAttributeInfo final
	{
		std::string Name;
		ShaderDataType DataType;
	};

	struct ShaderUniformInfo final
	{
		std::string Name;
		ShaderDataType DataType;
		i32 Location;
	};

	std::string GetShaderDataTypeName(ShaderDataType type);
	ShaderDataType GetShaderDataTypeFromName(const std::string& name);
}
