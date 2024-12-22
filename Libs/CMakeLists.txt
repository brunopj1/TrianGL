# Global libraries

add_subdirectory(glm)
add_subdirectory(stb_image)

# Debug / Release libraries

if (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Release")
    add_subdirectory(glad)
    add_subdirectory(glfw)
    add_subdirectory(soloud)
endif ()

# Debug libraries

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory(imgui)
endif ()

# Testing libraries

if (CMAKE_BUILD_TYPE STREQUAL "Testing")
    add_subdirectory(googletest)
endif ()