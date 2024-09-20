#ifndef TESTING

#define GLAD_GL_IMPLEMENTATION // NOLINT(clang-diagnostic-unused-macros)
#define GLFW_INCLUDE_NONE

#include "RenderBackend.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#ifdef IMGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#endif

#ifdef DEBUG
#include <format>
#include <iostream>
#endif

using namespace TGL;

// NOLINTBEGIN(CppMemberFunctionMayBeStatic)

void RenderBackend::SetErrorCallback(void (*func)(i32, const char*))
{
	glfwSetErrorCallback(func);
}

bool RenderBackend::InitGlfw()
{
	return glfwInit();
}

bool RenderBackend::InitGlad()
{
	return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); // NOLINT(clang-diagnostic-cast-function-type-strict)
}

bool RenderBackend::InitImgui(GLFWwindow* windowPtr) // NOLINT(CppParameterNeverUsed)
{
#ifdef IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::GetIO().IniFilename = nullptr;

	ImGui::StyleColorsDark();

	if (!ImGui_ImplGlfw_InitForOpenGL(windowPtr, true))
	{
		return false;
	}

	if (!ImGui_ImplOpenGL3_Init("#version 430"))
	{
		return false;
	}
#endif

	return true;
}

void RenderBackend::SetupOpenGlVersion(const i32 majorVersion, const i32 minorVersion, const bool coreProfile)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, coreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);
}

void RenderBackend::DebugVersions()
{
#ifdef DEBUG
	std::cout << "GLFW version: " << glfwGetVersionString() << '\n';
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << '\n';
#ifdef IMGUI
	std::cout << "Dear ImGui version: " << ImGui::GetVersion() << '\n';
#endif
#endif
}

void RenderBackend::SetupOpenGlSettings()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void RenderBackend::TerminateGlfw()
{
	glfwTerminate();
}

void RenderBackend::TerminateImgui()
{
#ifdef IMGUI
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif
}

GLFWwindow* RenderBackend::CreateGlfwWindow(const std::string& title, const glm::uvec2& resolution, const glm::uvec2& minResolution)
{
	GLFWwindow* windowPtr = glfwCreateWindow(resolution.x, resolution.y, title.c_str(), nullptr, nullptr);

	if (windowPtr != nullptr)
	{
		glfwMakeContextCurrent(windowPtr);
	}

	glfwSetWindowSizeLimits(windowPtr, minResolution.x, minResolution.y, GLFW_DONT_CARE, GLFW_DONT_CARE);

	return windowPtr;
}

void RenderBackend::DestroyGlfwWindow(GLFWwindow* windowPtr)
{
	glfwDestroyWindow(windowPtr);
}

void RenderBackend::ClearBuffers(const glm::vec3& color)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(color.r, color.g, color.b, 1.0f);
}

void RenderBackend::SwapBuffers(GLFWwindow* windowPtr)
{
	glfwSwapBuffers(windowPtr);
}

void RenderBackend::PrepareImguiFrame()
{
#ifdef IMGUI
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
#endif
}

void RenderBackend::RenderImguiFrame()
{
#ifdef IMGUI
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}

void RenderBackend::RenderImGuiDebugInfo(const u32 framerate, const u32 entityCount, const u32 componentCount) // NOLINT(CppParameterNeverUsed)
{
#ifdef DEBUG
#ifdef IMGUI
	const f32 frameTime = 1000.0f / (framerate != 0 ? framerate : 1);

	std::string message = std::format("Framerate: {0} ({1:.3f} ms)\n", framerate, frameTime);
	message += std::format("Entities: {0} | Components: {1}", entityCount, componentCount);

	const char* cMessage = message.c_str();

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	const ImVec2 windowPos = viewport->WorkPos + ImVec2(10, viewport->WorkSize.y - ImGui::CalcTextSize(cMessage).y - 10);

	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	drawList->AddText(windowPos, IM_COL32(255, 255, 255, 255), cMessage);
#endif
#endif
}

void RenderBackend::SetSwapInterval(const bool vsync)
{
	glfwSwapInterval(vsync);
}

void RenderBackend::SetViewport(const glm::uvec2& resolution)
{
	glViewport(0, 0, resolution.x, resolution.y);
}

void RenderBackend::DrawElements(const u32 vao, const u32 ebo, const u32 vertexCount)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
}

void RenderBackend::DrawElementsInstanced(const u32 vao, const u32 ebo, const u32 vertexCount, const u32 instanceCount)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glDrawElementsInstanced(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr, instanceCount);

	glBindVertexArray(0);
}

void RenderBackend::GenerateBuffer(u32& buffer, const BufferType bufferType)
{
	const i32 glBufferType = static_cast<i32>(bufferType);
	glGenBuffers(1, &buffer);
	glBindBuffer(glBufferType, buffer);
}

void RenderBackend::GenerateVertexArray(u32& vao)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void RenderBackend::DeleteBuffer(const u32 buffer)
{
	glDeleteBuffers(1, &buffer);
}

void RenderBackend::DeleteVertexArray(const u32 vao)
{
	glDeleteVertexArrays(1, &vao);
}

void RenderBackend::SetVertexAttributePointer(const u32 index, const i32 count, const VertexAttributeDataType dataType, const bool normalized, const u32 stride, const u32 offset)
{
	const i32 glDataType = static_cast<i32>(dataType);
	glVertexAttribPointer(index, count, glDataType, normalized, stride, reinterpret_cast<void*>(static_cast<uintptr_t>(offset))); // NOLINT(performance-no-int-to-ptr)
	glEnableVertexAttribArray(index);
}

void RenderBackend::SetVertexAttributePointerForInstancing(const u32 index, const i32 count, const VertexAttributeDataType dataType, const bool normalized, const u32 stride, const u32 offset)
{
	const i32 glDataType = static_cast<i32>(dataType);
	glVertexAttribPointer(index, count, glDataType, normalized, stride, reinterpret_cast<void*>(static_cast<uintptr_t>(offset))); // NOLINT(performance-no-int-to-ptr)
	glEnableVertexAttribArray(index);
	glVertexAttribDivisor(index, 1);
}

void RenderBackend::SetBufferData(const u32 buffer, const BufferType bufferType, const BufferDrawType drawType, const u32 byteSize, const void* data)
{
	const i32 glBufferType = static_cast<i32>(bufferType);
	const i32 glDrawType = static_cast<i32>(drawType);
	glBindBuffer(glBufferType, buffer);
	glBufferData(glBufferType, byteSize, data, glDrawType);
}

void RenderBackend::UpdateBufferData(const u32 buffer, const BufferType bufferType, const u32 byteOffset, const u32 byteSize, const void* data)
{
	const i32 glBufferType = static_cast<i32>(bufferType);
	glBindBuffer(glBufferType, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, byteOffset, byteSize, data);
}

void RenderBackend::BindBuffer(const u32 buffer, const BufferType bufferType)
{
	const i32 glBufferType = static_cast<i32>(bufferType);
	glBindBuffer(glBufferType, buffer);
}

void RenderBackend::UnbindVertexArray()
{
	glBindVertexArray(0);
}

void RenderBackend::GenerateTexture(u32& textureId)
{
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void RenderBackend::DeleteTexture(const u32 textureId)
{
	glDeleteTextures(1, &textureId);
}

void RenderBackend::SetTextureWrapMode(TextureWrapMode wrapMode)
{
	const i32 glWrapParameter = static_cast<i32>(wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glWrapParameter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glWrapParameter);
}

void RenderBackend::SetTextureFilterMode(const TextureFilterMode filterMode, const TextureFilterMode mipmapFilterMode, const bool usingMipmaps)
{
	const i32 glMagFilterParameter = static_cast<i32>(filterMode);
	i32 glMinFilterParameter = glMagFilterParameter;

	if (usingMipmaps)
	{
		if (filterMode == TextureFilterMode::Linear)
		{
			glMinFilterParameter = mipmapFilterMode == TextureFilterMode::Linear ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_NEAREST;
		}
		else // (parameters.Filter == TextureFilterMode::Nearest)
		{
			glMinFilterParameter = mipmapFilterMode == TextureFilterMode::Linear ? GL_NEAREST_MIPMAP_LINEAR : GL_NEAREST_MIPMAP_NEAREST;
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glMinFilterParameter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glMagFilterParameter);
}

void RenderBackend::SetTextureData(const glm::uvec2& resolution, const u8* data)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resolution.x, resolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void RenderBackend::GenerateTextureMipmaps()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}

void RenderBackend::BindTexture(const u32 textureId, const u32 slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void RenderBackend::UnbindTexture(const u32 slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, 0);
}

u32 RenderBackend::CreateProgram()
{
	return glCreateProgram();
}

u32 RenderBackend::CreateShader(ShaderType shaderType)
{
	const i32 glShaderType = static_cast<i32>(shaderType);
	return glCreateShader(glShaderType);
}

void RenderBackend::DeleteProgram(const u32 programId)
{
	glDeleteProgram(programId);
}

void RenderBackend::DetachShader(const u32 programId, const u32 shaderId)
{
	glDetachShader(programId, shaderId);
}

void RenderBackend::DeleteShader(const u32 shaderId)
{
	glDeleteShader(shaderId);
}

bool RenderBackend::CompileShader(const u32 shaderId, const std::string& shaderSource, std::string& errorLog)
{
	const char* shaderSourcePtr = shaderSource.c_str();

	glShaderSource(shaderId, 1, &shaderSourcePtr, nullptr);
	glCompileShader(shaderId);

	i32 success = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

	if (success == 0)
	{
		i32 logLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

		char* log = new char[logLength + 1];
		glGetShaderInfoLog(shaderId, logLength, nullptr, log);

		errorLog = log;
		delete[] log;

		return false;
	}

	return true;
}

void RenderBackend::AttachShader(const u32 programId, const u32 shaderId)
{
	glAttachShader(programId, shaderId);
}

bool RenderBackend::LinkProgram(const u32 programId, std::string& errorLog)
{
	glLinkProgram(programId);

	i32 success = 0;
	glGetProgramiv(programId, GL_LINK_STATUS, &success);

	if (success == 0)
	{
		i32 logLength = 0;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

		char* log = new char[logLength + 1];
		glGetProgramInfoLog(programId, logLength, nullptr, log);

		errorLog = log;
		delete[] log;

		return false;
	}

	return true;
}

std::vector<ShaderUniformInfo> RenderBackend::GetShaderUniforms(const u32 programId)
{
	i32 uniformCount = 0;
	glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &uniformCount);

	std::vector<ShaderUniformInfo> uniforms(uniformCount);

	constexpr u32 bufSize = 1024;
	char name[bufSize];
	i32 nameLength;

	u32 uniformDataType;
	i32 uniformSize;

	for (i32 i = 0; i < uniformCount; i++)
	{
		ShaderUniformInfo& uniform = uniforms[i];
		glGetActiveUniform(programId, i, bufSize, &nameLength, &uniformSize, &uniformDataType, name);
		uniform.Name = name;
		uniform.Location = glGetUniformLocation(programId, name);
		uniform.DataType = static_cast<UniformDataType>(uniformDataType);
		uniform.Size = uniformSize;
	}

	return uniforms;
}

void RenderBackend::UseProgram(const u32 programId)
{
	glUseProgram(programId);
}

// NOLINTBEGIN(CppInconsistentNaming)

void RenderBackend::SetUniform1i(const i32 location, const i32 value)
{
	glUniform1i(location, value);
}

void RenderBackend::SetUniform2i(const i32 location, const glm::ivec2& value)
{
	glUniform2iv(location, 1, &value[0]);
}

void RenderBackend::SetUniform3i(const i32 location, const glm::ivec3& value)
{
	glUniform3iv(location, 1, &value[0]);
}

void RenderBackend::SetUniform4i(const i32 location, const glm::ivec4& value)
{
	glUniform4iv(location, 1, &value[0]);
}

void RenderBackend::SetUniform1ui(const i32 location, const u32 value)
{
	glUniform1ui(location, value);
}

void RenderBackend::SetUniform2ui(const i32 location, const glm::uvec2& value)
{
	glUniform2uiv(location, 1, &value[0]);
}

void RenderBackend::SetUniform3ui(const i32 location, const glm::uvec3& value)
{
	glUniform3uiv(location, 1, &value[0]);
}

void RenderBackend::SetUniform4ui(const i32 location, const glm::uvec4& value)
{
	glUniform4uiv(location, 1, &value[0]);
}

void RenderBackend::SetUniform1f(const i32 location, const f32 value)
{
	glUniform1f(location, value);
}

void RenderBackend::SetUniform2f(const i32 location, const glm::vec2& value)
{
	glUniform2fv(location, 1, &value[0]);
}

void RenderBackend::SetUniform3f(const i32 location, const glm::vec3& value)
{
	glUniform3fv(location, 1, &value[0]);
}

void RenderBackend::SetUniform4f(const i32 location, const glm::vec4& value)
{
	glUniform4fv(location, 1, &value[0]);
}

void RenderBackend::SetUniformMatrix2f(const i32 location, const glm::mat2& value)
{
	glUniformMatrix2fv(location, 1, GL_FALSE, &value[0][0]);
}

void RenderBackend::SetUniformMatrix3f(const i32 location, const glm::mat3& value)
{
	glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
}

void RenderBackend::SetUniformMatrix4f(const i32 location, const glm::mat4& value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}

// NOLINTEND(CppInconsistentNaming)
// NOLINTEND(CppMemberFunctionMayBeStatic)

#endif
