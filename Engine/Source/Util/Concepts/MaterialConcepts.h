#pragma once

#include <type_traits>
#include <string>

namespace TGL
{
    // Forward declarations
    class Material;
    class MaterialUniform;
    class Shader;
    
    template <typename T, typename ...Args>
    concept SpawnableMaterial =
        !std::is_same_v<Material, T> &&
        std::is_base_of_v<Material, T> &&
        std::is_constructible_v<T, Args...>;
    
    template <typename T>
    concept SpawnableMaterialUniform =
        !std::is_same_v<MaterialUniform, T> &&
        std::is_base_of_v<MaterialUniform, T> &&
        std::is_constructible_v<T, const Shader*, const std::string&>;
}
