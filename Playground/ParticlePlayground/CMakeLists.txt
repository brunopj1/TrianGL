add_executable(ParticlePlayground)

# Include directories

target_include_directories(ParticlePlayground PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/
)

# Source files

target_sources(ParticlePlayground PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/MouseParticleEmitter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Entities/MouseParticleEmitter.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/GameMode/ParticlePlaygroundGameMode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/GameMode/ParticlePlaygroundGameMode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Main.cpp
)
        
# Dependencies

target_link_libraries(ParticlePlayground PRIVATE Engine)

# Copy assets to the binary directory

get_target_property(ENGINE_SOURCE_DIR Engine SOURCE_DIR)

add_custom_command(
        TARGET ParticlePlayground
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ENGINE_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:ParticlePlayground>/Assets"
        COMMENT "Copying the engine assets to the build directory..."
)

add_custom_command(
        TARGET ParticlePlayground
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:ParticlePlayground>/Assets"
        COMMENT "Copying the game assets to the build directory..."
)