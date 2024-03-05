#pragma once

#include "Internal/ManagedResource.h"
#include <string>

// Forward declaration
namespace Engine::Core
{
    class ResourceManager;
}

namespace Engine::Components
{
    class TextureRenderer;
}

namespace Engine::Resources
{
    class Shader : public Internal::ManagedResource
    {
    private:
        friend class Core::ResourceManager;
        friend class Components::TextureRenderer;

    private:
        std::string m_VertexShaderPath;
        std::string m_FragmentShaderPath;

    private:
        int m_ProgramId = 0;
        int m_VertexShaderId = 0;
        int m_FragmentShaderId = 0;

    private:
        Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
        ~Shader() override;

    public:
        std::string GetVertexShaderPath() const;
        std::string GetFragmentShaderPath() const;

    private:
        void Load();
        void Free();

        static int CompileShader(const std::string& filePath, int type);
        static std::string ReadShaderFile(const std::string& filePath);

    private:
        void Use() const;
    };
}
