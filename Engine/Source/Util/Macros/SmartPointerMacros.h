#pragma once

// ReSharper disable CppClangTidyBugproneMacroParentheses

#include <type_traits>

#define LAZY_POINTER_TEMPLATE_CONDITION       \
    std::enable_if_t<                         \
        std::is_base_of_v<TGL::Entity, T> ||  \
        std::is_base_of_v<TGL::Component, T>> 

#define SHARED_POINTER_TEMPLATE_CONDITION \
    std::enable_if_t<                     \
        std::is_base_of_v<TGL::Asset, T>> 