add_library(Engine STATIC)

# Include directories

target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/
)

# Source files

target_sources(Engine PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Internal/Quad.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Internal/Quad.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Internal/Shader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Internal/Shader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Internal/ShaderInfo.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Internal/ShaderInfo.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Internal/Sprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Internal/Sprite.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Animation.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Animation.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/AnimationSprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/AnimationSprite.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Audio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Audio.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Material.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Material.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/MaterialUniforms.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/MaterialUniforms.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/Texture.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/TextureSlice.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Assets/TextureSlice.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Internal/Concepts/EntitySystemConcepts.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Internal/Concepts/MaterialConcepts.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Internal/Concepts/ParticleSystemConcepts.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Internal/Concepts/ServiceCollection.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Internal/Concepts/SmartPointerConcepts.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Internal/Macros/AssetFactoryMacros.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Internal/Macros/ClassMacros.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Internal/Macros/EntityFactoryMacros.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Internal/Macros/EventMacros.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Internal/Macros/TestMacros.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Backends/AudioBackend.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Backends/AudioBackendDefault.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Backends/AudioBackendMock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Backends/InputBackend.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Backends/InputBackendDefault.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Backends/InputBackendMock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Backends/RenderBackend.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Backends/RenderBackendDefault.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Backends/RenderBackendMock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Private/AssetManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Private/AssetManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Private/EntityManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Private/EntityManager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Public/Clock.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Public/Clock.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Public/InputSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Public/InputSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Public/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Services/Public/Window.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Application.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/DataTypes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/InputCodes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/MemoryLeakDetection.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/Service.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core/ServiceCollection.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Events/WindowEvents.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Exceptions/Assets/IncompatibleMaterialException.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Exceptions/Assets/InvalidMaterialUniformException.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Exceptions/Common/FileNotFoundException.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Exceptions/Core/FailedToInitializeEngineException.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Exceptions/OpenGL/OpenGlException.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Exceptions/OpenGL/ShaderCompilationException.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Exceptions/OpenGL/ShaderLinkingException.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game/Internal/Renderable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game/Internal/Renderable.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game/Component.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game/Component.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game/Entity.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game/Entity.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game/GameMode.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game/GameMode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game/GameObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game/GameObject.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game/Transform.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game/Transform.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/General/Camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/General/Camera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Implementations/Materials/DefaultParticleMaterial.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Implementations/Materials/DefaultParticleMaterial.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Implementations/Materials/DefaultSpriteMaterial.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Implementations/Materials/DefaultSpriteMaterial.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Implementations/ParticleSystems/DefaultParticleSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Implementations/ParticleSystems/DefaultParticleSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Memory/LazyPtr.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Memory/SharedPtr.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Rendering/Animator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Rendering/Animator.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Rendering/AudioPlayer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Rendering/AudioPlayer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Rendering/ParticleSystem.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Rendering/ParticleSystem.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Rendering/SpriteRenderer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Rendering/SpriteRenderer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Util/RandomNumberGenerator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Util/RandomNumberGenerator.h
)

# Dependencies

target_link_libraries(Engine PUBLIC glm)

target_link_libraries(Engine PRIVATE stb_image)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Testing")
    target_link_libraries(Engine PRIVATE glad)
    target_link_libraries(Engine PRIVATE glfw)
    target_link_libraries(Engine PRIVATE soloud)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(Engine PUBLIC imgui)
endif ()
