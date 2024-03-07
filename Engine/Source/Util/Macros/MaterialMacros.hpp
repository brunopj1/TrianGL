#pragma once

#include <type_traits>

#define ATTRIBUTE_TEMPLATE_SPAWN_CONDITION              \
    std::enable_if_t<                                   \
        !std::is_same_v<MaterialAttribute, T> &&        \
        !std::is_same_v<TextureMaterialAttribute, T> && \
        std::is_base_of_v<MaterialAttribute, T> &&      \
        std::is_constructible_v<T, int>>
