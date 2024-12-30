add_executable(Snake)

# Include directories

target_include_directories(Snake PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/
)

# Source files

target_sources(Snake PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/Apple.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/Apple.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/AudioManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/AudioManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/Grid.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/Grid.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/ParticleEmitter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/ParticleEmitter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/Snake.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/Snake.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/SnakeBody.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/SnakeBody.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/GameMode/RenderingOrder.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/GameMode/SnakeGameMode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/GameMode/SnakeGameMode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Materials/GrassMaterial.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Materials/GrassMaterial.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Main.cpp
)
        
# Dependencies

target_link_libraries(Snake PRIVATE Engine)

# Copy assets to the binary directory

get_target_property(ENGINE_SOURCE_DIR Engine SOURCE_DIR)

add_custom_command(
        TARGET Snake
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ENGINE_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:Snake>/Assets"
        COMMENT "Copying the engine assets to the build directory..."
)

add_custom_command(
        TARGET Snake
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:Snake>/Assets"
        COMMENT "Copying the game assets to the build directory..."
)