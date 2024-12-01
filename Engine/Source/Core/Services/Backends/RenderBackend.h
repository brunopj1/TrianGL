#pragma once

#include "Assets/Internal/ShaderInfo.h"
#include "Assets/Texture.h"
#include "Core/DataTypes.h"
#include "Core/Internal/Concepts/ParticleSystemConcepts.h"
#include "Core/Internal/Macros/TestMacros.h"
#include "Core/Service.h"
#include "glm/mat2x2.hpp"
#include "glm/mat3x3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include <string>

// Forward declarations
struct GLFWwindow; // NOLINT(CppInconsistentNaming, IdentifierTypo)

namespace TGL
{
	// Forward declarations
	enum class ParticleDataType : u16;

	// clang-format off
    
    enum class BufferType : u16
    {
        ArrayBuffer        = 0x8892, // GL_ARRAY_BUFFER
        ElementArrayBuffer = 0x8893  // GL_ELEMENT_ARRAY_BUFFER
    };

    enum class BufferDrawType : u16
    {
        StaticDraw  = 0x88E4, // GL_STATIC_DRAW
        DynamicDraw = 0x88E8, // GL_DYNAMIC_DRAW
        StreamDraw  = 0x88E0  // GL_STREAM_DRAW
    };

    enum class VertexAttributeDataType : u16
    {
        I8  = 0x1400, // GL_BYTE
        U8  = 0x1401, // GL_UNSIGNED_BYTE
        I16 = 0x1402, // GL_SHORT
        U16 = 0x1403, // GL_UNSIGNED_SHORT
        I32 = 0x1404, // GL_INT
        U32 = 0x1405, // GL_UNSIGNED_INT
        F32 = 0x1406  // GL_FLOAT
    };

	struct VertexAttributeInfo
	{
		VertexAttributeDataType DataType;
		u8 DataSize;
		u8 ByteSize;
	};

    enum class ShaderType : u16
    {
        Vertex   = 0x8B31, // GL_VERTEX_SHADER
        TessCtrl = 0x8E88, // GL_TESS_CONTROL_SHADER
        TessEval = 0x8E87, // GL_TESS_EVALUATION_SHADER
        Geometry = 0x8DD9, // GL_GEOMETRY_SHADER
        Fragment = 0x8B30, // GL_FRAGMENT_SHADER
        Compute  = 0x91B9  // GL_COMPUTE_SHADER
    };

	// clang-format on

	class RenderBackend : public Service<RenderBackend> // NOLINT(CppClassCanBeFinal)
	{
	private:
		friend class Application;
		friend class ServiceCollection;
		friend struct ServiceDeleter<RenderBackend>;

		friend class Window;
		friend class Texture;
		friend class Sprite;
		friend class TextureSlice;
		friend class SpriteUniform;
		friend class Shader;
		friend class Quad;
		friend class SpriteRenderer;

		template <ValidCpuParticleData CpuParticle, ValidGpuParticleData GpuParticle, typename ParticleSpawnData>
		friend class ParticleSystem;

		template <typename T, ShaderDataType DataType>
		friend class MaterialUniformImpl;

	protected:
		RenderBackend() = default;
		~RenderBackend() = default;

	protected:
		MOCKABLE_METHOD void SetErrorCallback(void (*func)(i32, const char*));

	protected:
		MOCKABLE_METHOD bool InitGlfw();
		MOCKABLE_METHOD bool InitGlad();
		MOCKABLE_METHOD bool InitImgui(GLFWwindow* windowPtr);

		MOCKABLE_METHOD void SetupOpenGlVersion(i32 majorVersion, i32 minorVersion, bool coreProfile);
		MOCKABLE_METHOD void DebugVersions();

		MOCKABLE_METHOD void SetupOpenGlSettings();

		MOCKABLE_METHOD void TerminateGlfw();
		MOCKABLE_METHOD void TerminateImgui();

		MOCKABLE_METHOD GLFWwindow* CreateGlfwWindow(const std::string& title, const glm::uvec2& resolution, const glm::uvec2& minResolution);
		MOCKABLE_METHOD void DestroyGlfwWindow(GLFWwindow* windowPtr);

	protected:
		MOCKABLE_METHOD void ClearBuffers(const glm::vec3& color);
		MOCKABLE_METHOD void SwapBuffers(GLFWwindow* windowPtr);

	protected:
		MOCKABLE_METHOD void PrepareImguiFrame();
		MOCKABLE_METHOD void RenderImguiFrame();
		MOCKABLE_METHOD void RenderImGuiDebugInfo(u32 framerate, u32 entityCount, u32 componentCount);

	protected:
		MOCKABLE_METHOD void SetSwapInterval(bool vsync);
		MOCKABLE_METHOD void SetViewport(const glm::uvec2& resolution);

	protected:
		MOCKABLE_METHOD void DrawElements(u32 vao, u32 ebo, u32 vertexCount);
		MOCKABLE_METHOD void DrawElementsInstanced(u32 vao, u32 ebo, u32 vertexCount, u32 instanceCount);

	protected:
		MOCKABLE_METHOD void GenerateBuffer(u32& buffer, BufferType bufferType);
		MOCKABLE_METHOD void GenerateVertexArray(u32& vao);

		MOCKABLE_METHOD void DeleteBuffer(u32 buffer);
		MOCKABLE_METHOD void DeleteVertexArray(u32 vao);

		MOCKABLE_METHOD void SetVertexAttributePointer(u32 index, i32 count, VertexAttributeDataType dataType, bool normalized, u32 stride, u32 offset);
		MOCKABLE_METHOD void SetVertexAttributePointerForInstancing(u32 index, i32 count, VertexAttributeDataType dataType, bool normalized, u32 stride, u32 offset);

		MOCKABLE_METHOD void SetBufferData(u32 buffer, BufferType bufferType, BufferDrawType drawType, u32 byteSize, const void* data);
		MOCKABLE_METHOD void UpdateBufferData(u32 buffer, BufferType bufferType, u32 byteOffset, u32 byteSize, const void* data);

		MOCKABLE_METHOD void BindBuffer(u32 buffer, BufferType bufferType);
		MOCKABLE_METHOD void UnbindVertexArray();

	protected:
		MOCKABLE_METHOD void GenerateTexture(u32& textureId);
		MOCKABLE_METHOD void DeleteTexture(u32 textureId);

		MOCKABLE_METHOD void SetTextureWrapMode(TextureWrapMode wrapMode);
		MOCKABLE_METHOD void SetTextureFilterMode(TextureFilterMode filterMode, TextureFilterMode mipmapFilterMode, bool usingMipmaps);
		MOCKABLE_METHOD void SetTextureData(const glm::uvec2& resolution, const u8* data);
		MOCKABLE_METHOD void GenerateTextureMipmaps();

		MOCKABLE_METHOD void BindTexture(u32 textureId, u32 slot);
		MOCKABLE_METHOD void UnbindTexture(u32 slot);

	protected:
		MOCKABLE_METHOD u32 CreateProgram();
		MOCKABLE_METHOD u32 CreateShader(ShaderType shaderType);

		MOCKABLE_METHOD void DeleteProgram(u32 programId);
		MOCKABLE_METHOD void DetachShader(u32 programId, u32 shaderId);
		MOCKABLE_METHOD void DeleteShader(u32 shaderId);

		MOCKABLE_METHOD bool CompileShader(u32 shaderId, const std::string& shaderSource, std::string& errorLog);
		MOCKABLE_METHOD void AttachShader(u32 programId, u32 shaderId);
		MOCKABLE_METHOD bool LinkProgram(u32 programId, std::string& errorLog);

		MOCKABLE_METHOD std::vector<ShaderAttributeInfo> GetShaderAttributes(u32 programId);
		MOCKABLE_METHOD std::vector<ShaderUniformInfo> GetShaderUniforms(u32 programId);

		MOCKABLE_METHOD void UseProgram(u32 programId);

	protected:
		// NOLINTBEGIN(CppInconsistentNaming)
		MOCKABLE_METHOD void SetUniform1i(i32 location, i32 value);
		MOCKABLE_METHOD void SetUniform2i(i32 location, const glm::ivec2& value);
		MOCKABLE_METHOD void SetUniform3i(i32 location, const glm::ivec3& value);
		MOCKABLE_METHOD void SetUniform4i(i32 location, const glm::ivec4& value);
		MOCKABLE_METHOD void SetUniform1ui(i32 location, u32 value);
		MOCKABLE_METHOD void SetUniform2ui(i32 location, const glm::uvec2& value);
		MOCKABLE_METHOD void SetUniform3ui(i32 location, const glm::uvec3& value);
		MOCKABLE_METHOD void SetUniform4ui(i32 location, const glm::uvec4& value);
		MOCKABLE_METHOD void SetUniform1f(i32 location, f32 value);
		MOCKABLE_METHOD void SetUniform2f(i32 location, const glm::vec2& value);
		MOCKABLE_METHOD void SetUniform3f(i32 location, const glm::vec3& value);
		MOCKABLE_METHOD void SetUniform4f(i32 location, const glm::vec4& value);
		MOCKABLE_METHOD void SetUniformMatrix2f(i32 location, const glm::mat2& value);
		MOCKABLE_METHOD void SetUniformMatrix3f(i32 location, const glm::mat3& value);
		MOCKABLE_METHOD void SetUniformMatrix4f(i32 location, const glm::mat4& value);
		// NOLINTEND(CppInconsistentNaming)
	};
}
