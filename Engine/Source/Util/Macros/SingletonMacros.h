#pragma once

#include <cassert>

#ifdef DEBUG
#define ASSERT_SINGLETON_AVAILABILITY() assert(s_IsAvailable && "Cannot call this method because the application is not running")
#else
#define ASSERT_SINGLETON_AVAILABILITY()
#endif

#ifdef DEBUG
#define ASSERT_SINGLETON_OBJECT_CREATION() assert(s_CanCreateAndDestroyObjects && "Cannot create the object because the application is not running")
#else
#define ASSERT_SINGLETON_OBJECT_CREATION() if (!s_CanCreateAndDestroyObjects) return nullptr
#endif

#ifdef DEBUG
#define ASSERT_SINGLETON_OBJECT_CREATION_NO_RET() assert(s_CanCreateAndDestroyObjects && "Cannot create the object because the application is not running")
#else
#define ASSERT_SINGLETON_OBJECT_CREATION_NO_RET() if (!s_CanCreateAndDestroyObjects) return
#endif

#ifdef DEBUG
#define ASSERT_SINGLETON_OBJECT_DESTRUCTION() assert(s_CanCreateAndDestroyObjects && "Cannot destroy the object because the application is not running")
#else
#define ASSERT_SINGLETON_OBJECT_DESTRUCTION() if (!s_CanCreateAndDestroyObjects) return
#endif
