add_library(STB-Image INTERFACE)

set_target_properties(STB-Image PROPERTIES LINKER_LANGUAGE C)

# Include directories

target_include_directories(STB-Image INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/stb_image/
)
