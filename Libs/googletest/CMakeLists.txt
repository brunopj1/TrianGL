add_library(googletest STATIC)

set_target_properties(googletest PROPERTIES LINKER_LANGUAGE CXX)

# Include directories

target_include_directories(googletest PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/
)

target_include_directories(googletest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/
)

# Source files

target_sources(googletest PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/gtest-assertion-result.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/gtest-death-test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/gtest-matchers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/gtest-message.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/gtest-param-test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/gtest-printers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/gtest-spi.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/gtest-test-part.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/gtest-typed-test.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/gtest.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/gtest_pred_impl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/gtest_prod.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/internal/custom/gtest-port.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/internal/custom/gtest-printers.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/internal/custom/gtest.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/internal/gtest-death-test-internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/internal/gtest-filepath.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/internal/gtest-internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/internal/gtest-param-util.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/internal/gtest-port-arch.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/internal/gtest-port.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/internal/gtest-string.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include/gtest/internal/gtest-type-util.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-all.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-assertion-result.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-death-test.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-filepath.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-internal-inl.h
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-matchers.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-port.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-printers.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-test-part.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-typed-test.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest_main.cc
)