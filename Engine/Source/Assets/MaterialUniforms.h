#pragma once

#include "glm/glm.hpp"
#include "Util/Macros/MaterialMacros.h"
#include <string>
#include <memory>

namespace TGL
{
    // Forward declaration
    class Shader;
    class Sprite;

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

    // Sprite uniform

    class SpriteUniform final : public MaterialUniform
    {
    private:
        friend class AssetManager;

    private:
        int m_MatrixLocation;
        int m_ResoultionLocation;
        unsigned char m_Slot;

    public:
        std::shared_ptr<Sprite> Value;

    public:
        SpriteUniform(const Shader* shader, const std::string& name);
        ~SpriteUniform() override = default;

    private:
        bool IsValid() const override;
        void BindInternal() const override;
    };
}
