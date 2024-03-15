#pragma once

#include "Resources/Internal/Shader.h"
#include "Util/Macros/SingletonMacros.hpp"

#include <string>
#include <unordered_map>

namespace TGL
{
    class ResourceManager
    {
    private:
        friend class Application;
        friend class Material;
        friend class Texture;

    private:
        DECLARE_SINGLETON_INSTANCE_VAR(TGL::ResourceManager);

    private:
        std::unordered_map<Shader*, unsigned int, ShaderHash, ShaderEqual> m_Shaders;

    private:
        ResourceManager();
        ~ResourceManager();

    private:
        static Shader* LoadShader(const std::string& vertexShader, const std::string& fragmentShader, bool isFilePath);
        static void UnloadShader(Shader* shader);
    };
}
