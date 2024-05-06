#pragma once

#include <cassert>

#ifdef DEBUG
#define ASSERT_APPLICATION_AVAILABILITY() assert(s_IsAvailable && "Cannot call this method because the application is not running")
#else
#define ASSERT_APPLICATION_AVAILABILITY() static_assert(true, "")
#endif

#ifdef DEBUG
#define ASSERT_APPLICATION_OBJECT_CREATION() assert(s_CanCreateAndDestroyObjects && "Cannot create the object because the application is not running")
#else
#define ASSERT_APPLICATION_OBJECT_CREATION() static_assert(true, "")
#endif

#ifdef DEBUG
#define ASSERT_APPLICATION_OBJECT_DESTRUCTION() assert(s_CanCreateAndDestroyObjects && "Cannot destroy the object because the application is not running")
#else
#define ASSERT_APPLICATION_OBJECT_DESTRUCTION() static_assert(true, "")
#endif
