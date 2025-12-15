# Setup options

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

set(GLFW_USE_HYBRID_HPG ON)
set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF)

set(BUILD_SHARED_LIBS OFF)

if (WIN32)
    set(GLFW_BUILD_WIN32 ON)
    set(GLFW_BUILD_COCOA OFF)
    set(GLFW_BUILD_X11 OFF)
    set(GLFW_BUILD_WAYLAND OFF)
elseif (APPLE)
    set(GLFW_BUILD_WIN32 OFF)
    set(GLFW_BUILD_COCOA ON)
    set(GLFW_BUILD_X11 OFF)
    set(GLFW_BUILD_WAYLAND OFF)
elseif (UNIX)
    set(GLFW_BUILD_WIN32 OFF)
    set(GLFW_BUILD_COCOA OFF)
    set(GLFW_BUILD_X11 ON)
    set(GLFW_BUILD_WAYLAND OFF) # TODO add wayland support
else ()
    message(FATAL_ERROR "Unsupported platform")
endif ()

# Add the glfw CMakeLists

add_subdirectory(glfw)