#pragma once

#include <type_traits>

#define UNIFORM_TEMPLATE_SPAWN_CONDITION                               \
    std::enable_if_t<                                                  \
        !std::is_same_v<MaterialUniform, T> &&                         \
        std::is_constructible_v<T, const Shader*, const std::string&>>

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
