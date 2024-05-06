﻿#pragma once

#include "Assets/Texture.h" // Required for SharedPtr<Sprite>
#include "glm/glm.hpp"
#include "Util/Memory/SharedPtr.h"
#include <string>

namespace TGL
{
    // Forward declaration
    class Shader;

    // Base class
    class MaterialUniform
    {
    private:
        friend class AssetManager;
        friend class Material;

    protected:
        int m_Location;

    protected:
        MaterialUniform(const Shader* shader, const std::string& name);
        virtual ~MaterialUniform();

    public:
        MaterialUniform(const MaterialUniform&) = delete;
        MaterialUniform& operator=(const MaterialUniform&) = delete;
        MaterialUniform(MaterialUniform&&) = delete;
        MaterialUniform& operator=(MaterialUniform&&) = delete;

    private:
        virtual bool IsValid() const;
        void Bind() const;
        virtual void BindInternal() const = 0;
    };

    // Template class

    template<typename T>
    class MaterialUniformImpl final : public MaterialUniform
    {
    public:
        T Value;

    public:
        MaterialUniformImpl(const Shader* shader, const std::string& name)
            : MaterialUniform(shader, name), Value() {}
        
        ~MaterialUniformImpl() override = default;

    private:
        void BindInternal() const override;
    };
    
    // Common implementations

    using IntUniform = MaterialUniformImpl<int>;
    
    using Int2Uniform = MaterialUniformImpl<glm::ivec2>;
    
    using Int3Uniform = MaterialUniformImpl<glm::ivec3>;
    
    using Int4Uniform = MaterialUniformImpl<glm::ivec4>;
    
    using UintUniform = MaterialUniformImpl<unsigned int>;
    
    using Uint2Uniform = MaterialUniformImpl<glm::uvec2>;
    
    using Uint3Uniform = MaterialUniformImpl<glm::uvec3>;
    
    using Uint4Uniform = MaterialUniformImpl<glm::uvec4>;
    
    using FloatUniform = MaterialUniformImpl<float>;
    
    using Float2Uniform = MaterialUniformImpl<glm::vec2>;
    
    using Float3Uniform = MaterialUniformImpl<glm::vec3>;
    
    using Float4Uniform = MaterialUniformImpl<glm::vec4>;
    
    using Mat2Uniform = MaterialUniformImpl<glm::mat2>;
    
    using Mat3Uniform = MaterialUniformImpl<glm::mat3>;
    
    using Mat4Uniform = MaterialUniformImpl<glm::mat4>;
    
    // Sprite uniform

    // TODO also use the template class for the SpriteUniform
    
    class SpriteUniform final : public MaterialUniform
    {
    private:
        friend class AssetManager;

    private:
        int m_MatrixLocation;
        int m_ResolutionLocation;
        unsigned char m_Slot;

    public:
        SharedPtr<Sprite> Value;

    public:
        SpriteUniform(const Shader* shader, const std::string& name);
        ~SpriteUniform() override = default;

    private:
        bool IsValid() const override;
        void BindInternal() const override;
    };
}
