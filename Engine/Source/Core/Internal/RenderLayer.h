#pragma once

#include "Assets/Texture.h"
#include "Core/DataTypes.h"

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat2x2.hpp"
#include "glm/mat3x3.hpp"
#include "glm/mat4x4.hpp"
#include <string>

// Forward declarations
struct GLFWwindow; // NOLINT(CppInconsistentNaming, IdentifierTypo)

namespace TGL
{
    // @formatter:off
    
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
        F32 = 0x1406, // GL_FLOAT
        F64 = 0x140A  // GL_DOUBLE
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

    // @formatter:on

    struct ShaderUniformInfo final
    {
        std::string Name;
        i32 Size;
        u32 DataType;
        i32 Location;
    };
    
    class RenderLayer final
    {
    private:
        friend class Application;
        friend class AssetManager;
        friend class Window;
        friend class Texture;
        friend class Sprite;
        friend class TextureSlice;
        friend class SpriteUniform;
        friend class Shader;
        friend class SpriteRenderer;
        friend class ParticleSystem;
        
        template <typename T>
        friend class MaterialUniformImpl;
        
    public:
        RenderLayer() = delete;
        ~RenderLayer() = delete;

    private:
        static void SetErrorCallback(void(*func)(i32, const char*));

        static void SetWindowPositionCallback(GLFWwindow* windowPtr, void(*func)(GLFWwindow*, i32, i32));
        static void SetWindowSizeCallback(GLFWwindow* windowPtr, void(*func)(GLFWwindow*, i32, i32));
        static void SetWindowMaximizeCallback(GLFWwindow* windowPtr, void(*func)(GLFWwindow*, i32));
        static void SetWindowMinimizeCallback(GLFWwindow* windowPtr, void(*func)(GLFWwindow*, i32));
        
    private:
        static bool InitGlfw();
        static bool InitGlad();
        static bool InitImgui(GLFWwindow* windowPtr);
        
        static void SetupOpenGlVersion(i32 majorVersion, i32 minorVersion, bool coreProfile);
        static void DebugVersions();

        static void SetupOpenGlSettings();

        static void TerminateGlfw();
        static void TerminateImgui();
        
        static GLFWwindow* CreateGlfwWindow(const std::string& title, const glm::uvec2& resolution, const glm::uvec2& minResolution);
        static void DestroyGlfwWindow(GLFWwindow* windowPtr);

    private:
        static void ClearBuffers(const glm::vec3& color);
        static void SwapBuffers(GLFWwindow* windowPtr);

    private:
        static void PrepareImguiFrame();
        static void RenderImguiFrame();
        static void RenderImGuiDebugInfo(u32 framerate, u32 entityCount, u32 componentCount);

    private:
        static void CloseWindow(GLFWwindow* windowPtr);
        static bool ShouldCloseWindow(GLFWwindow* windowPtr);
        
    private:
        static void SetWindowTitle(GLFWwindow* windowPtr, const std::string& title);
        static void SetWindowPosition(GLFWwindow* windowPtr, const glm::ivec2& position);
        static void SetWindowResolution(GLFWwindow* windowPtr, const glm::uvec2& resolution);
        
    private:
        static void SetFullscreen(GLFWwindow* windowPtr, bool fullscreen, const glm::uvec2& position, const glm::uvec2& resolution);
        static void MaximizeWindow(GLFWwindow* windowPtr);
        static void MinimizeWindow(GLFWwindow* windowPtr);
        static void RestoreWindow(GLFWwindow* windowPtr);

        static bool IsMaximized(GLFWwindow* windowPtr);
        static bool IsMinimized(GLFWwindow* windowPtr);

    private:
        static void SetSwapInterval(bool vsync);
        static void SetViewport(const glm::uvec2& resolution);

    private:
        static void DrawElements(u32 vao, u32 ebo, u32 vertexCount);
        static void DrawElementsInstanced(u32 vao, u32 ebo, u32 vertexCount, u32 instanceCount);

    private:
        static void GenerateBuffer(u32& buffer, BufferType bufferType);
        static void GenerateVertexArray(u32& vao);
        
        static void DeleteBuffer(u32 buffer);
        static void DeleteVertexArray(u32 vao);

        static void SetVertexAttributePointer(u32 index, i32 count, VertexAttributeDataType dataType, bool normalized, u32 stride, u32 offset);
        static void SetVertexAttributePointerForInstancing(u32 index, i32 count, VertexAttributeDataType dataType, bool normalized, u32 stride, u32 offset);
        
        static void SetBufferData(u32 buffer, BufferType bufferType, BufferDrawType drawType, u32 byteSize, const void* data);
        static void UpdateBufferData(u32 buffer, BufferType bufferType, u32 byteOffset, u32 byteSize, const void* data);

        static void BindBuffer(u32 buffer, BufferType bufferType);
        static void UnbindVertexArray();
        
    private:
        static void GenerateTexture(u32& textureId);
        static void DeleteTexture(u32 textureId);

        static void SetTextureWrapMode(TextureWrapMode wrapMode);
        static void SetTextureFilterMode(TextureFilterMode filterMode, TextureFilterMode mipmapFilterMode, bool usingMipmaps);
        static void SetTextureData(const glm::uvec2& resolution, const u8* data);
        static void GenerateTextureMipmaps();

        static void BindTexture(u32 textureId, u32 slot);
        static void UnbindTexture(u32 slot);

    private:
        static u32 CreateProgram();
        static u32 CreateShader(ShaderType shaderType);
        
        static void DeleteProgram(u32 programId);
        static void DeleteShader(u32 shaderId);

        static bool CompileShader(u32 shaderId, const std::string& shaderSource, std::string& errorLog);
        static void AttachShader(u32 programId, u32 shaderId);
        static bool LinkProgram(u32 programId, std::string& errorLog);
        
        static std::vector<ShaderUniformInfo> GetShaderUniforms(u32 programId);

        static void UseProgram(u32 programId);
        
    private:
        // NOLINTBEGIN(CppInconsistentNaming)
        static void SetUniform1i(i32 location, i32 value);
        static void SetUniform2iv(i32 location, const glm::ivec2& value);
        static void SetUniform3iv(i32 location, const glm::ivec3& value);
        static void SetUniform4iv(i32 location, const glm::ivec4& value);
        static void SetUniform1ui(i32 location, u32 value);
        static void SetUniform2uiv(i32 location, const glm::uvec2& value);
        static void SetUniform3uiv(i32 location, const glm::uvec3& value);
        static void SetUniform4uiv(i32 location, const glm::uvec4& value);
        static void SetUniform1f(i32 location, f32 value);
        static void SetUniform2fv(i32 location, const glm::vec2& value);
        static void SetUniform3fv(i32 location, const glm::vec3& value);
        static void SetUniform4fv(i32 location, const glm::vec4& value);
        static void SetUniformMatrix2fv(i32 location, const glm::mat2& value);
        static void SetUniformMatrix3fv(i32 location, const glm::mat3& value);
        static void SetUniformMatrix4fv(i32 location, const glm::mat4& value);
        // NOLINTEND(CppInconsistentNaming)
    };
}

