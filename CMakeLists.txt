cmake_minimum_required(VERSION 3.15)

# Project

project(TrianGL VERSION 1.0 LANGUAGES C CXX)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG latest # Replace with a specific tag or commit for stability
)

# Configurations

set(CMAKE_CONFIGURATION_TYPES Debug Release Testing CACHE STRING "Available configurations" FORCE)

# C++ Standard

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configuration dependant flags and definitions

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g)
    add_compile_definitions(DEBUG IMGUI)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3)
    add_compile_definitions(NDEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Testing")
    add_compile_options(-g)
    add_compile_options(--coverage)
    add_link_options(--coverage)
    add_compile_definitions(DEBUG TESTING)
endif ()

# Engine

add_subdirectory(Engine)
add_subdirectory(Libs)

# Tests

if (CMAKE_BUILD_TYPE STREQUAL "Testing")
    add_subdirectory(Tests)
endif ()

# Playgrounds

if (NOT CMAKE_BUILD_TYPE STREQUAL "Testing")
    add_subdirectory(Playground/AnimationPlayground)
    add_subdirectory(Playground/AudioPlayground)
    add_subdirectory(Playground/ParticlePlayground)
endif ()

# Games

if (NOT CMAKE_BUILD_TYPE STREQUAL "Testing")
    add_subdirectory(Games/Fantasyland)
    add_subdirectory(Games/Snake)
endif ()