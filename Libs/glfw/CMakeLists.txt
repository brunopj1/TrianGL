add_library(GLFW STATIC)

set_target_properties(GLFW PROPERTIES LINKER_LANGUAGE C)

# Include directories

target_include_directories(GLFW PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include/
)

# Source files

target_sources(GLFW PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include/GLFW/glfw3.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include/GLFW/glfw3native.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/context.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/egl_context.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/init.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/input.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/mappings.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/monitor.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/null_init.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/null_joystick.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/null_joystick.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/null_monitor.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/null_platform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/null_window.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/osmesa_context.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/platform.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/platform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/vulkan.c
        ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/window.c
)

if (WIN32)
    target_sources(GLFW PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/egl_context.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/osmesa_context.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/wgl_context.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/win32_init.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/win32_joystick.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/win32_module.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/win32_monitor.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/win32_thread.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/win32_thread.h
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/win32_time.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/win32_time.h
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/win32_window.c
    )
elseif (UNIX)
    target_sources(GLFW PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/egl_context.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/glx_context.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/linux_joystick.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/osmesa_context.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/posix_thread.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/posix_time.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/x11_init.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/x11_monitor.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/x11_window.c
            ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src/xkb_unicode.c
    )
endif ()

# Macro Definitions

if (WIN32)
    target_compile_definitions(GLFW PRIVATE _GLFW_WIN32)
elseif (UNIX)
    target_compile_definitions(GLFW PRIVATE _GLFW_X11)
endif ()