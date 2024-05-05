#pragma once

#include <type_traits>

namespace TGL 
{
    // Forward declarations
    class Entity;
    class Component;
    
    class Material;
    class Audio;
    class Texture;
    class TextureSlice;
    class Sprite;
    
    template <typename T>
    concept LazyPointerValue =
        std::is_base_of_v<Entity, T> ||
        std::is_base_of_v<Component, T>;
        
    template <typename T>
    concept SharedPointerValue =
        std::is_same_v<Audio, T> ||
        std::is_base_of_v<Material, T> ||
        std::is_same_v<Texture, T> ||
        std::is_same_v<TextureSlice, T> ||
        std::is_same_v<Sprite, T>;
}

