#pragma once

#include "glm/glm.hpp"

// TODO prevent users from manually creating / deleting these classes

namespace Engine::Resources
{
    // Forward declaration
    class Material;
    class Texture;

    // Base class
    class MaterialAttribute
    {
    private:
        friend class Material;

    protected:
        int m_Location;

    protected:
        MaterialAttribute(int location);
        virtual ~MaterialAttribute() = default;

    public:
        MaterialAttribute(const MaterialAttribute&) = delete;
        MaterialAttribute& operator=(const MaterialAttribute&) = delete;
        MaterialAttribute(MaterialAttribute&&) = delete;
        MaterialAttribute& operator=(MaterialAttribute&&) = delete;

    private:
        void Bind() const;
        virtual void BindInternal() const = 0;
    };

    // Texture attribute

    class TextureMaterialAttribute final : public MaterialAttribute
    {
    private:
        Texture* m_Value;
        unsigned int m_Slot;

    public:
        TextureMaterialAttribute(int location, unsigned int slot);
        ~TextureMaterialAttribute() override = default;

    public:
        Texture* GetValue() const;
        void SetValue(Texture* value);

        unsigned int GetSlot() const;
        void SetSlot(unsigned int slot);

    private:
        void BindInternal() const override;
    };

    // Macro

    // @formatter:off
    
    #define MATERIAL_ATTRIBUTE_IMPLEMENTATION(name, type, val) \
        class name final : public MaterialAttribute            \
        {                                                      \
        private:                                               \
            type m_Value;                                      \
                                                               \
        public:                                                \
            name(const int location)                           \
                : MaterialAttribute(location), m_Value(val) {} \
            ~name() override = default;                        \
                                                               \
        public:                                                \
            type GetValue() const                              \
            {                                                  \
                return m_Value;                                \
            }                                                  \
                                                               \
            void SetValue(const type value)                    \
            {                                                  \
                m_Value = value;                               \
            }                                                  \
                                                               \
        private:                                               \
            void BindInternal() const override;                \
        }

    // @formatter:on

    // Regular implementations

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(IntMaterialAttribute, int, 0);

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(Int2MaterialAttribute, glm::ivec2, {});

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(Int3MaterialAttribute, glm::ivec3, {});

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(Int4MaterialAttribute, glm::ivec4, {});

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(UintMaterialAttribute, unsigned int, 0);

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(Uint2MaterialAttribute, glm::uvec2, {});

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(Uint3MaterialAttribute, glm::uvec3, {});

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(Uint4MaterialAttribute, glm::uvec4, {});

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(FloatMaterialAttribute, float, 0.0f);

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(Float2MaterialAttribute, glm::vec2, {});

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(Float3MaterialAttribute, glm::vec3, {});

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(Float4MaterialAttribute, glm::vec4, {});

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(Mat2MaterialAttribute, glm::mat2, {});

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(Mat3MaterialAttribute, glm::mat3, {});

    MATERIAL_ATTRIBUTE_IMPLEMENTATION(Mat4MaterialAttribute, glm::mat4, {});
}
