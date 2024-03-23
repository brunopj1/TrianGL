﻿#pragma once

#include "glm/glm.hpp"
#include <string>
#include <memory>

namespace TGL
{
    // Forward declaration
    class Shader;
    class TextureBinding;

    // Base class
    class MaterialUniform
    {
    private:
        friend class ResourceManager;
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

    // Macro

    // @formatter:off
    
    #define MATERIAL_UNIFORM_IMPLEMENTATION(className, type, val)    \
        class className final : public MaterialUniform               \
        {                                                            \
        public:                                                      \
            type Value;                                              \
                                                                     \
        public:                                                      \
            className(const Shader* shader, const std::string& name) \
                : MaterialUniform(shader, name), Value(val) {}       \
            ~className() override = default;                         \
                                                                     \
        private:                                                     \
            void BindInternal() const override;                      \
        }

    // @formatter:on

    // Common implementations

    MATERIAL_UNIFORM_IMPLEMENTATION(IntUniform, int, 0);

    MATERIAL_UNIFORM_IMPLEMENTATION(Int2Uniform, glm::ivec2, {});

    MATERIAL_UNIFORM_IMPLEMENTATION(Int3Uniform, glm::ivec3, {});

    MATERIAL_UNIFORM_IMPLEMENTATION(Int4Uniform, glm::ivec4, {});

    MATERIAL_UNIFORM_IMPLEMENTATION(UintUniform, unsigned int, 0);

    MATERIAL_UNIFORM_IMPLEMENTATION(Uint2Uniform, glm::uvec2, {});

    MATERIAL_UNIFORM_IMPLEMENTATION(Uint3Uniform, glm::uvec3, {});

    MATERIAL_UNIFORM_IMPLEMENTATION(Uint4Uniform, glm::uvec4, {});

    MATERIAL_UNIFORM_IMPLEMENTATION(FloatUniform, float, 0.0f);

    MATERIAL_UNIFORM_IMPLEMENTATION(Float2Uniform, glm::vec2, {});

    MATERIAL_UNIFORM_IMPLEMENTATION(Float3Uniform, glm::vec3, {});

    MATERIAL_UNIFORM_IMPLEMENTATION(Float4Uniform, glm::vec4, {});

    MATERIAL_UNIFORM_IMPLEMENTATION(Mat2Uniform, glm::mat2, {});

    MATERIAL_UNIFORM_IMPLEMENTATION(Mat3Uniform, glm::mat3, {});

    MATERIAL_UNIFORM_IMPLEMENTATION(Mat4Uniform, glm::mat4, {});

    // Texture uniform

    class TextureUniform final : public MaterialUniform
    {
    private:
        friend class ResourceManager;

    private:
        int m_MatrixLocation;
        int m_ResoultionLocation;
        unsigned char m_Slot;

    public:
        std::shared_ptr<TextureBinding> Value;

    public:
        TextureUniform(const Shader* shader, const std::string& name);
        ~TextureUniform() override = default;

    private:
        bool IsValid() const override;
        void BindInternal() const override;
    };
}
