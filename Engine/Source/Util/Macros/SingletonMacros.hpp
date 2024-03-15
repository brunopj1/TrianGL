#pragma once

#include <cassert>

#define DECLARE_SINGLETON_INSTANCE_VAR(class) static inline class* s_Instance = nullptr

#define ASSERT_SINGLETON_INITIALIZED(class) assert(class::s_Instance != nullptr && "The singleton #class is not initialized")
