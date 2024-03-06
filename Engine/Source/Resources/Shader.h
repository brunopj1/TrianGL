#pragma once

#include "Internal/ManagedResource.h"
#include <string>
#include <unordered_map>

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
    // Forward declaration
    class Material;

    class Shader final : public Internal::ManagedResource
    {
    private:
        friend class Core::ResourceManager;
        friend class Components::TextureRenderer; // TODO remove friend class
        friend class Material;

    private:
        std::string m_VertexShader;
        std::string m_FragmentShader;
        bool m_IsFilePath;

        std::unordered_map<std::string, int> m_UniformLocations;

    private:
        int m_ProgramId = 0;
        int m_VertexShaderId = 0;
        int m_FragmentShaderId = 0;

    private:
        Shader(std::string vertexShader, std::string fragmentShader, bool isFilePath);
        ~Shader() override;

    private:
        void Load();
        void Free();

    private:
        void LinkProgram();
        int CompileShader(const std::string& shader, int type) const;
        static std::string ReadShaderFile(const std::string& filePath);

    private:
        void LoadUniformLocations();
        int GetUniformLocation(const std::string& name) const;

    private:
        void Use() const;
    };
}
