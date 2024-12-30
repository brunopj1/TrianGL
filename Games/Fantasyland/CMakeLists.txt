add_executable(Fantasyland)

# Include directories

target_include_directories(Fantasyland PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/
)

# Source files

target_sources(Fantasyland PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Characters/Player/Player.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Characters/Player/Player.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Characters/CharacterDirection.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/GameMode/FantasylandGameMode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/GameMode/FantasylandGameMode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Services/AssetCollection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Services/AssetCollection.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Main.cpp
)
        
# Dependencies

target_link_libraries(Fantasyland PRIVATE Engine)

# Copy assets to the binary directory

get_target_property(ENGINE_SOURCE_DIR Engine SOURCE_DIR)

add_custom_command(
        TARGET Fantasyland
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ENGINE_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:Fantasyland>/Assets"
        COMMENT "Copying the engine assets to the build directory..."
)

add_custom_command(
        TARGET Fantasyland
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:Fantasyland>/Assets"
        COMMENT "Copying the game assets to the build directory..."
)