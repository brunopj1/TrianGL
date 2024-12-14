add_library(IMGUI STATIC)

set_target_properties(IMGUI PROPERTIES LINKER_LANGUAGE CXX)

# Include directories

target_include_directories(IMGUI PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp/
)

# Source files

target_sources(IMGUI PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imconfig.h
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_internal.h
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_tables.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.h
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_rectpack.h
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_textedit.h
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imstb_truetype.h
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp/imgui_stdlib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp/imgui_stdlib.h
)

# Macro Definitions

target_compile_definitions(IMGUI PUBLIC IMGUI_DEFINE_MATH_OPERATORS)

target_compile_definitions(IMGUI PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

if (WIN32)
    target_compile_definitions(IMGUI PRIVATE _IMGUI_WIN32)
elseif (UNIX)
    target_compile_definitions(IMGUI PRIVATE _IMGUI_X11)
endif ()

# Dependencies

target_link_libraries(IMGUI PRIVATE GLAD)
target_link_libraries(IMGUI PRIVATE GLFW)
