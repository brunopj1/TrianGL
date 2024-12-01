#include "Quad.h"

#include "Core/Services/Backends/RenderBackend.h"

using namespace TGL;

void Quad::Init()
{
	// clang-format off

	constexpr f32 vertices[] = {
		// Positions     // Tex Coords
		-0.5f, -0.5f,    0.0f, 0.0f,    // Bottom Left
		 0.5f, -0.5f,    1.0f, 0.0f,    // Bottom Right
		-0.5f,  0.5f,    0.0f, 1.0f,    // Top Left
		 0.5f,  0.5f,    1.0f, 1.0f     // Top Right
	};

	constexpr u32 indices[] = {
		0, 1, 2, // Bottom Left Triangle
		1, 3, 2  // Top Right Triangle
	};

	// clang-format on

	RenderBackend& renderBackend = RenderBackend::Get();

	renderBackend.GenerateVertexArray(m_Vao);

	renderBackend.GenerateBuffer(m_Vbo, BufferType::ArrayBuffer);
	renderBackend.SetBufferData(m_Vbo, BufferType::ArrayBuffer, BufferDrawType::StaticDraw, sizeof(vertices), vertices);

	renderBackend.GenerateBuffer(m_Ebo, BufferType::ElementArrayBuffer);
	renderBackend.SetBufferData(m_Ebo, BufferType::ElementArrayBuffer, BufferDrawType::StaticDraw, sizeof(indices), indices);

	SetupQuadVertexAttributes();

	renderBackend.UnbindVertexArray();

	m_ShaderAttributes.reserve(2);
	m_ShaderAttributes.push_back(ShaderDataType::FVEC2); // Position
	m_ShaderAttributes.push_back(ShaderDataType::FVEC2); // Tex Coord
}
void Quad::Terminate()
{
	RenderBackend& renderBackend = RenderBackend::Get();

	renderBackend.DeleteBuffer(m_Vbo);
	m_Vbo = 0;

	renderBackend.DeleteBuffer(m_Ebo);
	m_Ebo = 0;

	renderBackend.DeleteVertexArray(m_Vao);
	m_Vao = 0;
}

u32 Quad::GetVao() const
{
	return m_Vao;
}

u32 Quad::GetVbo() const
{
	return m_Vbo;
}

u32 Quad::GetEbo() const
{
	return m_Ebo;
}

const std::vector<ShaderDataType>& Quad::GetShaderAttributes() const
{
	return m_ShaderAttributes;
}

void Quad::SetupQuadVertexAttributes() const // NOLINT(CppMemberFunctionMayBeStatic)
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetVertexAttributePointer(0, 2, VertexAttributeDataType::F32, false, 4 * sizeof(f32), 0);
	renderBackend.SetVertexAttributePointer(1, 2, VertexAttributeDataType::F32, false, 4 * sizeof(f32), 2 * sizeof(f32));
}
