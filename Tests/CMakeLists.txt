add_executable(Tests)

# Include directories

target_include_directories(Tests PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/
)

# Source files

target_sources(Tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Assets/Animation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Assets/AnimationSprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Assets/Audio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Assets/Internal/Shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Assets/Internal/Sprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Assets/Material.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Assets/MaterialUniforms.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Assets/Texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Assets/TextureSlice.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Core/Services/Public/Clock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Core/Services/Public/InputSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Core/Services/Public/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Events/WindowEvents.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Game/Component.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Game/Entity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Game/GameMode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Game/GameObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Game/Internal/Renderable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Game/Transform.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/General/Camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Memory/LazyPtr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Memory/SharedPtr.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Rendering/Animator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Rendering/AudioPlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Rendering/ParticleSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Rendering/SpriteRenderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Tests/Util/RandomNumberGenerator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Util/GameTestAbstractions.h
)
        
# Dependencies

target_link_libraries(Tests PRIVATE Engine)
target_link_libraries(Tests PRIVATE googletest)

# Copy assets to the binary directory

get_target_property(ENGINE_SOURCE_DIR Engine SOURCE_DIR)

add_custom_command(
        TARGET Tests
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ENGINE_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:Tests>/Assets"
        COMMENT "Copying the engine assets to the build directory..."
)

add_custom_command(
        TARGET Tests
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets" "$<TARGET_FILE_DIR:Tests>/Assets"
        COMMENT "Copying the game assets to the build directory..."
)