#pragma once

#include <type_traits>

#define LAZY_PONTER_TEMPLATE_CONDITION        \
    std::enable_if_t<                         \
        std::is_base_of_v<TGL::Entity, T> ||  \
        std::is_base_of_v<TGL::Component, T>>
