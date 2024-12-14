add_executable(AnimationPlayground)

# Include directories

target_include_directories(AnimationPlayground PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/
)

# Source files

target_sources(AnimationPlayground PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/AnimationTester.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/AnimationTester.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/AnimatorTester.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/AnimatorTester.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/GameMode/AnimationPlaygroundGameMode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/GameMode/AnimationPlaygroundGameMode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/WindowConstants.h
)
        
# Dependencies

target_link_libraries(AnimationPlayground PRIVATE Engine)

# Copy assets to the binary directory

add_custom_command(
        TARGET AnimationPlayground
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets" "${CMAKE_BINARY_DIR}/Assets"
        COMMENT "Copying the game assets to build directory..."
)

# Copy assets to the binary directory

get_target_property(ENGINE_SOURCE_DIR Engine SOURCE_DIR)

add_custom_command(
        TARGET AnimationPlayground
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ENGINE_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:AnimationPlayground>/Assets"
        COMMENT "Copying the engine assets to the build directory..."
)

add_custom_command(
        TARGET AnimationPlayground
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:AnimationPlayground>/Assets"
        COMMENT "Copying the game assets to the build directory..."
)