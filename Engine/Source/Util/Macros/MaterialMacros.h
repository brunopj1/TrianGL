#pragma once

// ReSharper disable CppClangTidyBugproneMacroParentheses

#include <type_traits>

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
