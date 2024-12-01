#include <Rendering/ParticleSystem.h>

using namespace TGL;

VertexAttributeInfo ParticleDataInfo::ConvertToVertexAttribute() const
{
	switch (DataType)
	{
		case ParticleDataType::INT:
			return {.DataType = VertexAttributeDataType::I32, .DataSize = 1, .ByteSize = 4};
		case ParticleDataType::UINT:
			return {.DataType = VertexAttributeDataType::U32, .DataSize = 1, .ByteSize = 4};
		case ParticleDataType::FLOAT:
			return {.DataType = VertexAttributeDataType::F32, .DataSize = 1, .ByteSize = 4};
		case ParticleDataType::IVEC2:
			return {.DataType = VertexAttributeDataType::I32, .DataSize = 2, .ByteSize = 4 * 2};
		case ParticleDataType::IVEC3:
			return {.DataType = VertexAttributeDataType::I32, .DataSize = 3, .ByteSize = 4 * 3};
		case ParticleDataType::IVEC4:
			return {.DataType = VertexAttributeDataType::I32, .DataSize = 4, .ByteSize = 4 * 4};
		case ParticleDataType::UVEC2:
			return {.DataType = VertexAttributeDataType::U32, .DataSize = 2, .ByteSize = 4 * 2};
		case ParticleDataType::UVEC3:
			return {.DataType = VertexAttributeDataType::U32, .DataSize = 3, .ByteSize = 4 * 3};
		case ParticleDataType::UVEC4:
			return {.DataType = VertexAttributeDataType::U32, .DataSize = 4, .ByteSize = 4 * 4};
		case ParticleDataType::FVEC2:
			return {.DataType = VertexAttributeDataType::F32, .DataSize = 2, .ByteSize = 4 * 2};
		case ParticleDataType::FVEC3:
			return {.DataType = VertexAttributeDataType::F32, .DataSize = 3, .ByteSize = 4 * 3};
		case ParticleDataType::FVEC4:
			return {.DataType = VertexAttributeDataType::F32, .DataSize = 4, .ByteSize = 4 * 4};
	}

	return {};
}
