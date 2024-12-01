#include "ShaderInfo.h"

using namespace TGL;

std::string TGL::GetShaderDataTypeName(const ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::INT:
			return "INT";
		case ShaderDataType::UINT:
			return "UINT";
		case ShaderDataType::FLOAT:
			return "FLOAT";
		case ShaderDataType::IVEC2:
			return "IVEC2";
		case ShaderDataType::IVEC3:
			return "IVEC3";
		case ShaderDataType::IVEC4:
			return "IVEC4";
		case ShaderDataType::UVEC2:
			return "UVEC2";
		case ShaderDataType::UVEC3:
			return "UVEC3";
		case ShaderDataType::UVEC4:
			return "UVEC4";
		case ShaderDataType::FVEC2:
			return "FVEC2";
		case ShaderDataType::FVEC3:
			return "FVEC3";
		case ShaderDataType::FVEC4:
			return "FVEC4";
		case ShaderDataType::MAT2:
			return "MAT2";
		case ShaderDataType::MAT3:
			return "MAT3";
		case ShaderDataType::MAT4:
			return "MAT4";
		case ShaderDataType::MAT2X3:
			return "MAT2X3";
		case ShaderDataType::MAT2X4:
			return "MAT2X4";
		case ShaderDataType::MAT3X2:
			return "MAT3X2";
		case ShaderDataType::MAT3X4:
			return "MAT3X4";
		case ShaderDataType::MAT4X2:
			return "MAT4X2";
		case ShaderDataType::MAT4X3:
			return "MAT4X3";
		case ShaderDataType::SAMPLER2D:
			return "SAMPLER2D";
		case ShaderDataType::INVALID:
			return "INVALID";
	}

	return "";
}

ShaderDataType TGL::GetShaderDataTypeFromName(const std::string& name)
{
	if (name == "int")
	{
		return ShaderDataType::INT;
	}
	if (name == "uint")
	{
		return ShaderDataType::UINT;
	}
	if (name == "float")
	{
		return ShaderDataType::FLOAT;
	}
	if (name == "ivec2")
	{
		return ShaderDataType::IVEC2;
	}
	if (name == "ivec3")
	{
		return ShaderDataType::IVEC3;
	}
	if (name == "ivec4")
	{
		return ShaderDataType::IVEC4;
	}
	if (name == "uvec2")
	{
		return ShaderDataType::UVEC2;
	}
	if (name == "uvec3")
	{
		return ShaderDataType::UVEC3;
	}
	if (name == "uvec4")
	{
		return ShaderDataType::UVEC4;
	}
	if (name == "vec2")
	{
		return ShaderDataType::FVEC2;
	}
	if (name == "vec3")
	{
		return ShaderDataType::FVEC3;
	}
	if (name == "vec4")
	{
		return ShaderDataType::FVEC4;
	}
	if (name == "mat2")
	{
		return ShaderDataType::MAT2;
	}
	if (name == "mat2x2")
	{
		return ShaderDataType::MAT2;
	}
	if (name == "mat3")
	{
		return ShaderDataType::MAT3;
	}
	if (name == "mat3x3")
	{
		return ShaderDataType::MAT3;
	}
	if (name == "mat4")
	{
		return ShaderDataType::MAT4;
	}
	if (name == "mat4x4")
	{
		return ShaderDataType::MAT4;
	}
	if (name == "mat2x3")
	{
		return ShaderDataType::MAT2X3;
	}
	if (name == "mat2x4")
	{
		return ShaderDataType::MAT2X4;
	}
	if (name == "mat3x2")
	{
		return ShaderDataType::MAT3X2;
	}
	if (name == "mat3x4")
	{
		return ShaderDataType::MAT3X4;
	}
	if (name == "mat4x2")
	{
		return ShaderDataType::MAT4X2;
	}
	if (name == "mat4x3")
	{
		return ShaderDataType::MAT4X3;
	}
	if (name == "sampler2D")
	{
		return ShaderDataType::SAMPLER2D;
	}
	return ShaderDataType::INVALID;
}
