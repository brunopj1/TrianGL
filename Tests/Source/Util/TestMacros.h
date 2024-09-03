#pragma once

#include "gtest/gtest.h"

#define TEST_GAME(test_suite_name, test_name, class_body)                        \
    TEST(test_suite_name, test_name)                                             \
    {                                                                            \
        class test_suite_name##_##test_name##_GameMode final : public GameMode   \
        class_body;                                                              \
                                                                                 \
        TGL::Application::Run<test_suite_name##_##test_name##_GameMode>({}, {}); \
    }
