add_executable(AudioPlayground)

# Include directories

target_include_directories(AudioPlayground PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/
)

# Source files

target_sources(AudioPlayground PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/AudioPlayerTester.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/AudioPlayerTester.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/AudioTester.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/AudioTester.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/GameMode/AudioPlaygroundGameMode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/GameMode/AudioPlaygroundGameMode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/WindowConstants.h
)
        
# Dependencies

target_link_libraries(AudioPlayground PRIVATE Engine)

# Copy assets to the binary directory

get_target_property(ENGINE_SOURCE_DIR Engine SOURCE_DIR)

add_custom_command(
        TARGET AudioPlayground
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ENGINE_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:AudioPlayground>/Assets"
        COMMENT "Copying the engine assets to the build directory..."
)

add_custom_command(
        TARGET AudioPlayground
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:AudioPlayground>/Assets"
        COMMENT "Copying the game assets to the build directory..."
)