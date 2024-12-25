# Setup options

set(BUILD_GMOCK OFF)
set(INSTALL_GTEST OFF)
set(GTEST_HAS_ABSL OFF)

set(gmock_build_tests OFF)
set(gtest_build_samples OFF)
set(gtest_disable_pthreads OFF)
set(gtest_hide_internal_symbols OFF)
set(gtest_force_shared_crt OFF)

# Add the googletest CMakeLists

add_subdirectory(googletest)