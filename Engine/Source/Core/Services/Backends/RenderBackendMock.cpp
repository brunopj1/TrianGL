﻿#ifdef TESTING

#include "RenderBackend.h"

using namespace TGL;

// NOLINTBEGIN(CppParameterNeverUsed)

void RenderBackend::SetErrorCallback(void (*func)(i32, const char*)) {}

bool RenderBackend::InitGlfw()
{
	return true;
}

bool RenderBackend::InitGlad()
{
	return true;
}

bool RenderBackend::InitImgui(GLFWwindow* windowPtr)
{
	return true;
}

void RenderBackend::SetupOpenGlVersion(i32 majorVersion, i32 minorVersion, bool coreProfile) {}

void RenderBackend::DebugVersions() {}

void RenderBackend::SetupOpenGlSettings() {}

void RenderBackend::TerminateGlfw() {}

void RenderBackend::TerminateImgui() {}

GLFWwindow* RenderBackend::CreateGlfwWindow(const std::string& title, const glm::uvec2& resolution, const glm::uvec2& minResolution)
{
	return (GLFWwindow*)0x1; // NOLINT(CppCStyleCast)
}

void RenderBackend::DestroyGlfwWindow(GLFWwindow* windowPtr) {}

void RenderBackend::ClearBuffers(const glm::vec3& color) {}

void RenderBackend::SwapBuffers(GLFWwindow* windowPtr) {}

void RenderBackend::PrepareImguiFrame() {}

void RenderBackend::RenderImguiFrame() {}

void RenderBackend::RenderImGuiDebugInfo(u32 framerate, u32 entityCount, u32 componentCount) {}

void RenderBackend::SetSwapInterval(bool vsync) {}

void RenderBackend::SetViewport(const glm::uvec2& resolution) {}

void RenderBackend::DrawElements(u32 vao, u32 ebo, u32 vertexCount) {}

void RenderBackend::DrawElementsInstanced(u32 vao, u32 ebo, u32 vertexCount, u32 instanceCount) {}

void RenderBackend::GenerateBuffer(u32& buffer, BufferType bufferType) {}

void RenderBackend::GenerateVertexArray(u32& vao) {}

void RenderBackend::DeleteBuffer(u32 buffer) {}

void RenderBackend::DeleteVertexArray(u32 vao) {}

void RenderBackend::SetVertexAttributePointer(u32 index, i32 count, VertexAttributeDataType dataType, bool normalized, u32 stride, u32 offset) {}

void RenderBackend::SetVertexAttributePointerForInstancing(u32 index, i32 count, VertexAttributeDataType dataType, bool normalized, u32 stride, u32 offset) {}

void RenderBackend::SetBufferData(u32 buffer, BufferType bufferType, BufferDrawType drawType, u32 byteSize, const void* data) {}

void RenderBackend::UpdateBufferData(u32 buffer, BufferType bufferType, u32 byteOffset, u32 byteSize, const void* data) {}

void RenderBackend::BindBuffer(u32 buffer, BufferType bufferType) {}

void RenderBackend::UnbindVertexArray() {}

void RenderBackend::GenerateTexture(u32& textureId) {}

void RenderBackend::DeleteTexture(u32 textureId) {}

void RenderBackend::SetTextureWrapMode(TextureWrapMode wrapMode) {}

void RenderBackend::SetTextureFilterMode(TextureFilterMode filterMode, TextureFilterMode mipmapFilterMode, bool usingMipmaps) {}

void RenderBackend::SetTextureData(const glm::uvec2& resolution, const u8* data) {}

void RenderBackend::GenerateTextureMipmaps() {}

void RenderBackend::BindTexture(u32 textureId, u32 slot) {}

void RenderBackend::UnbindTexture(u32 slot) {}

u32 RenderBackend::CreateProgram()
{
	return 1;
}

u32 RenderBackend::CreateShader(ShaderType shaderType)
{
	return 1;
}

void RenderBackend::DeleteProgram(u32 programId) {}

void RenderBackend::DeleteShader(u32 shaderId) {}

bool RenderBackend::CompileShader(u32 shaderId, const std::string& shaderSource, std::string& errorLog)
{
	return true;
}

void RenderBackend::AttachShader(u32 programId, u32 shaderId) {}


bool RenderBackend::LinkProgram(u32 programId, std::string& errorLog)
{
	return true;
}

std::vector<ShaderUniformInfo> RenderBackend::GetShaderUniforms(u32 programId)
{
	return {};
}

void RenderBackend::UseProgram(u32 programId) {}

// NOLINTBEGIN(CppInconsistentNaming)

void RenderBackend::SetUniform1i(int location, int value) {}

void RenderBackend::SetUniform2iv(int location, const glm::ivec2& value) {}

void RenderBackend::SetUniform3iv(int location, const glm::ivec3& value) {}

void RenderBackend::SetUniform4iv(int location, const glm::ivec4& value) {}

void RenderBackend::SetUniform1ui(int location, unsigned int value) {}

void RenderBackend::SetUniform2uiv(int location, const glm::uvec2& value) {}

void RenderBackend::SetUniform3uiv(int location, const glm::uvec3& value) {}

void RenderBackend::SetUniform4uiv(int location, const glm::uvec4& value) {}

void RenderBackend::SetUniform1f(int location, float value) {}

void RenderBackend::SetUniform2fv(int location, const glm::vec2& value) {}

void RenderBackend::SetUniform3fv(int location, const glm::vec3& value) {}

void RenderBackend::SetUniform4fv(int location, const glm::vec4& value) {}

void RenderBackend::SetUniformMatrix2fv(int location, const glm::mat2& value) {}

void RenderBackend::SetUniformMatrix3fv(int location, const glm::mat3& value) {}

void RenderBackend::SetUniformMatrix4fv(int location, const glm::mat4& value) {}

// NOLINTEND(CppInconsistentNaming)
// NOLINTEND(CppParameterNeverUsed)

#endif
