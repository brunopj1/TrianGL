#pragma once

// ReSharper disable CppClangTidyBugproneMacroParentheses

#define DELETE_COPY_AND_MOVE_CONSTRUCTORS(class_name)  \
public:                                                \
    class_name(const class_name&) = delete;            \
    class_name(class_name&&) = delete;                 \
    class_name& operator=(const class_name&) = delete; \
    class_name& operator=(class_name&&) = delete