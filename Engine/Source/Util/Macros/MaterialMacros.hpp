#pragma once

#include <type_traits>

#define UNIFORM_TEMPLATE_SPAWN_CONDITION       \
    std::enable_if_t<                          \
        !std::is_same_v<MaterialUniform, T> && \
        !std::is_same_v<TextureUniform &&      \
        std::is_constructible_v<T, int>>
