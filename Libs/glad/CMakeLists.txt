add_library(GLAD STATIC)

set_target_properties(GLAD PROPERTIES LINKER_LANGUAGE C)

# Include directories

target_include_directories(GLAD PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/
)

# Source files

target_sources(GLAD PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/glad/glad.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/include/KHR/khrplatform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c
)