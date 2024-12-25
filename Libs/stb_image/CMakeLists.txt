add_library(stb_image INTERFACE)

set_target_properties(stb_image PROPERTIES LINKER_LANGUAGE C)

# Include directories

target_include_directories(stb_image INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/stb_image/
)
