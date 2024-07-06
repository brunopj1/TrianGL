#pragma once

#include <Assets/Texture.h> // Required for SharedPtr<Sprite>
#include <glm/glm.hpp>
#include <Memory/SharedPtr.h>
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
        i32 m_Location;

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

    using IntUniform = MaterialUniformImpl<i32>;
    
    using Int2Uniform = MaterialUniformImpl<glm::ivec2>;
    
    using Int3Uniform = MaterialUniformImpl<glm::ivec3>;
    
    using Int4Uniform = MaterialUniformImpl<glm::ivec4>;
    
    using UintUniform = MaterialUniformImpl<u32>;
    
    using Uint2Uniform = MaterialUniformImpl<glm::uvec2>;
    
    using Uint3Uniform = MaterialUniformImpl<glm::uvec3>;
    
    using Uint4Uniform = MaterialUniformImpl<glm::uvec4>;
    
    using FloatUniform = MaterialUniformImpl<f32>;
    
    using Float2Uniform = MaterialUniformImpl<glm::vec2>;
    
    using Float3Uniform = MaterialUniformImpl<glm::vec3>;
    
    using Float4Uniform = MaterialUniformImpl<glm::vec4>;
    
    using Mat2Uniform = MaterialUniformImpl<glm::mat2>;
    
    using Mat3Uniform = MaterialUniformImpl<glm::mat3>;
    
    using Mat4Uniform = MaterialUniformImpl<glm::mat4>;
    
    // Sprite uniform

    class SpriteUniform final : public MaterialUniform
    {
    private:
        friend class AssetManager;

    private:
        i32 m_MatrixLocation;
        i32 m_ResolutionLocation;
        u8 m_Slot;

    public:
        SharedPtr<Sprite> Value;

    public:
        SpriteUniform(const Shader* shader, const std::string& name);
        ~SpriteUniform() override = default;

    public:
        bool HasValue() const;

    private:
        bool IsValid() const override;
        void BindInternal() const override;
    };
}
