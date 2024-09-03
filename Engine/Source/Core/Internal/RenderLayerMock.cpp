#ifdef TESTING

#include "Core/Services/Window.h"
#include "RenderLayer.h"

using namespace TGL;

// Mock variables

bool g_ShouldClose = false;

bool g_IsMaximized = false;
bool g_IsMinimized = false;

// NOLINTBEGIN(CppParameterNeverUsed)

void RenderLayer::SetErrorCallback(void (*func)(i32, const char*)) {}

void RenderLayer::SetWindowPositionCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32)) {}

void RenderLayer::SetWindowSizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32, i32)) {}

void RenderLayer::SetWindowMaximizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32)) {}

void RenderLayer::SetWindowMinimizeCallback(GLFWwindow* windowPtr, void (*func)(GLFWwindow*, i32)) {}

bool RenderLayer::InitGlfw()
{
	return true;
}

bool RenderLayer::InitGlad()
{
	return true;
}

bool RenderLayer::InitImgui(GLFWwindow* windowPtr)
{
	return true;
}

void RenderLayer::SetupOpenGlVersion(i32 majorVersion, i32 minorVersion, bool coreProfile) {}

void RenderLayer::DebugVersions() {}

void RenderLayer::SetupOpenGlSettings() {}

void RenderLayer::TerminateGlfw() {}

void RenderLayer::TerminateImgui() {}

GLFWwindow* RenderLayer::CreateGlfwWindow(const std::string& title, const glm::uvec2& resolution, const glm::uvec2& minResolution)
{
	return (GLFWwindow*)0x1; // NOLINT(CppCStyleCast)
}

void RenderLayer::DestroyGlfwWindow(GLFWwindow* windowPtr) {}

void RenderLayer::ClearBuffers(const glm::vec3& color) {}

void RenderLayer::SwapBuffers(GLFWwindow* windowPtr) {}

void RenderLayer::PrepareImguiFrame() {}

void RenderLayer::RenderImguiFrame() {}

void RenderLayer::RenderImGuiDebugInfo(u32 framerate, u32 entityCount, u32 componentCount) {}

void RenderLayer::CloseWindow(GLFWwindow* windowPtr)
{
	g_ShouldClose = true;
}

bool RenderLayer::ShouldCloseWindow(GLFWwindow* windowPtr)
{
	return g_ShouldClose;
}

void RenderLayer::SetWindowTitle(GLFWwindow* windowPtr, const std::string& title) {}

void RenderLayer::SetWindowPosition(GLFWwindow* windowPtr, const glm::ivec2& position)
{
	Window::PositionCallback(windowPtr, position.x, position.y);
}

void RenderLayer::SetWindowResolution(GLFWwindow* windowPtr, const glm::uvec2& resolution)
{
	Window::SizeCallback(windowPtr, resolution.x, resolution.y);
}

void RenderLayer::SetFullscreen(GLFWwindow* windowPtr, const bool fullscreen, const glm::uvec2& position, const glm::uvec2& resolution)
{
	Window::FullscreenCallback(fullscreen);
}

void RenderLayer::MaximizeWindow(GLFWwindow* windowPtr)
{
	g_IsMaximized = true;
	g_IsMinimized = false;

	Window::MaximizeCallback(windowPtr, 1);
}

void RenderLayer::MinimizeWindow(GLFWwindow* windowPtr)
{
	g_IsMinimized = true;
	g_IsMaximized = false;

	Window::MinimizeCallback(windowPtr, 1);
}

void RenderLayer::RestoreWindow(GLFWwindow* windowPtr)
{
	if (g_IsMaximized)
	{
		g_IsMaximized = false;
		Window::MaximizeCallback(windowPtr, 0);
	}
	else if (g_IsMinimized)
	{
		g_IsMinimized = false;
		Window::MinimizeCallback(windowPtr, 0);
	}
}

bool RenderLayer::IsMaximized(GLFWwindow* windowPtr)
{
	return g_IsMaximized;
}

bool RenderLayer::IsMinimized(GLFWwindow* windowPtr)
{
	return g_IsMinimized;
}

void RenderLayer::SetSwapInterval(bool vsync) {}

void RenderLayer::SetViewport(const glm::uvec2& resolution) {}

void RenderLayer::DrawElements(u32 vao, u32 ebo, u32 vertexCount) {}

void RenderLayer::DrawElementsInstanced(u32 vao, u32 ebo, u32 vertexCount, u32 instanceCount) {}

void RenderLayer::GenerateBuffer(u32& buffer, BufferType bufferType) {}

void RenderLayer::GenerateVertexArray(u32& vao) {}

void RenderLayer::DeleteBuffer(u32 buffer) {}

void RenderLayer::DeleteVertexArray(u32 vao) {}

void RenderLayer::SetVertexAttributePointer(u32 index, i32 count, VertexAttributeDataType dataType, bool normalized, u32 stride, u32 offset) {}

void RenderLayer::SetVertexAttributePointerForInstancing(u32 index, i32 count, VertexAttributeDataType dataType, bool normalized, u32 stride, u32 offset) {}

void RenderLayer::SetBufferData(u32 buffer, BufferType bufferType, BufferDrawType drawType, u32 byteSize, const void* data) {}

void RenderLayer::UpdateBufferData(u32 buffer, BufferType bufferType, u32 byteOffset, u32 byteSize, const void* data) {}

void RenderLayer::BindBuffer(u32 buffer, BufferType bufferType) {}

void RenderLayer::UnbindVertexArray() {}

void RenderLayer::GenerateTexture(u32& textureId) {}

void RenderLayer::DeleteTexture(u32 textureId) {}

void RenderLayer::SetTextureWrapMode(TextureWrapMode wrapMode) {}

void RenderLayer::SetTextureFilterMode(TextureFilterMode filterMode, TextureFilterMode mipmapFilterMode, bool usingMipmaps) {}

void RenderLayer::SetTextureData(const glm::uvec2& resolution, const u8* data) {}

void RenderLayer::GenerateTextureMipmaps() {}

void RenderLayer::BindTexture(u32 textureId, u32 slot) {}

void RenderLayer::UnbindTexture(u32 slot) {}

u32 RenderLayer::CreateProgram()
{
	return 1;
}

u32 RenderLayer::CreateShader(ShaderType shaderType)
{
	return 1;
}

void RenderLayer::DeleteProgram(u32 programId) {}

void RenderLayer::DeleteShader(u32 shaderId) {}

bool RenderLayer::CompileShader(u32 shaderId, const std::string& shaderSource, std::string& errorLog)
{
	return true;
}

void RenderLayer::AttachShader(u32 programId, u32 shaderId) {}


bool RenderLayer::LinkProgram(u32 programId, std::string& errorLog)
{
	return true;
}

std::vector<ShaderUniformInfo> RenderLayer::GetShaderUniforms(u32 programId)
{
	return {};
}

void RenderLayer::UseProgram(u32 programId) {}

// NOLINTBEGIN(CppInconsistentNaming)

void RenderLayer::SetUniform1i(int location, int value) {}

void RenderLayer::SetUniform2iv(int location, const glm::ivec2& value) {}

void RenderLayer::SetUniform3iv(int location, const glm::ivec3& value) {}

void RenderLayer::SetUniform4iv(int location, const glm::ivec4& value) {}

void RenderLayer::SetUniform1ui(int location, unsigned int value) {}

void RenderLayer::SetUniform2uiv(int location, const glm::uvec2& value) {}

void RenderLayer::SetUniform3uiv(int location, const glm::uvec3& value) {}

void RenderLayer::SetUniform4uiv(int location, const glm::uvec4& value) {}

void RenderLayer::SetUniform1f(int location, float value) {}

void RenderLayer::SetUniform2fv(int location, const glm::vec2& value) {}

void RenderLayer::SetUniform3fv(int location, const glm::vec3& value) {}

void RenderLayer::SetUniform4fv(int location, const glm::vec4& value) {}

void RenderLayer::SetUniformMatrix2fv(int location, const glm::mat2& value) {}

void RenderLayer::SetUniformMatrix3fv(int location, const glm::mat3& value) {}

void RenderLayer::SetUniformMatrix4fv(int location, const glm::mat4& value) {}

// NOLINTEND(CppInconsistentNaming)
// NOLINTEND(CppParameterNeverUsed)

#endif
