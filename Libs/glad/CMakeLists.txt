add_library(glad STATIC)

set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)

# Include directories

target_include_directories(glad PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/
)

# Source files

target_sources(glad PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/glad/glad.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/KHR/khrplatform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c
)