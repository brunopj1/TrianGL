#pragma once

#include <Core/ApplicationStatus.h>

#include <cassert>

#ifdef DEBUG
#define ASSERT_APPLICATION_AVAILABILITY() assert(ApplicationStatus::AreServicesAvailable() && "Cannot call this method because the application services are not available")
#else
#define ASSERT_APPLICATION_AVAILABILITY() static_assert(true, "")
#endif

#ifdef DEBUG
#define ASSERT_APPLICATION_OBJECT_CREATION() assert(ApplicationStatus::AreServicesAvailable() && "Cannot create the object because the application is not running")
#else
#define ASSERT_APPLICATION_OBJECT_CREATION() static_assert(true, "")
#endif

#ifdef DEBUG
#define ASSERT_APPLICATION_OBJECT_DESTRUCTION() assert(ApplicationStatus::AreServicesAvailable() && "Cannot destroy the object because the application is not running")
#else
#define ASSERT_APPLICATION_OBJECT_DESTRUCTION() static_assert(true, "")
#endif
