﻿#pragma once

#include <string>
#include <unordered_map>

namespace TGL
{
    class Shader final
    {
    private:
        friend class AssetManager;
        friend class Material;
        friend class MaterialUniform;
        friend class SpriteUniform;
        friend struct ShaderHash;
        friend struct ShaderEqual;

    private:
        std::string m_VertexShader;
        std::string m_FragmentShader;

        std::unordered_map<std::string, int> m_UniformLocations;

    private:
        int m_ProgramId = 0;
        int m_VertexShaderId = 0;
        int m_FragmentShaderId = 0;

    private:
        Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
        ~Shader() = default;

    private:
        void Init();
        void Free();

    private:
        void LinkProgram();
        static int CompileShader(const std::string& shaderPath, int type);
        static std::string ReadShaderFile(const std::string& filePath);

    private:
        void LoadUniformLocations();
        int GetUniformLocation(const std::string& name) const;

    private:
        void Use() const;
    };

    struct ShaderHash
    {
        std::size_t operator()(const Shader* shader) const;
    };

    struct ShaderEqual
    {
        bool operator()(const Shader* shader1, const Shader* shader2) const;
    };
}