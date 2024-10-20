#include <Core/Services/Private/AssetManager.h>

#define STB_IMAGE_IMPLEMENTATION

#include "Assets/Animation.h"
#include "Assets/AnimationSprite.h"
#include "Core/Services/Backends/AudioBackend.h"
#include <Assets/Audio.h>
#include <Assets/Material.h>
#include <Assets/Texture.h>
#include <Exceptions/Core/FailedToInitializeEngineException.h>
#include <format>
#include <stb_image.h>
#include <thread>

using namespace TGL;

// NOLINTBEGIN(CppMemberFunctionMayBeStatic)

void AssetManager::Init()
{
	// STBI
	stbi_set_flip_vertically_on_load(true);

	// SoLoud
	AudioBackend& audioBackend = AudioBackend::Get();

	int errorCode = 0;
	m_SoloudEngine = audioBackend.InitSoloud(errorCode);

	if (m_SoloudEngine == nullptr)
	{
		throw FailedToInitializeEngineException(std::format("Failed to init SoLoud (error code: {0})", errorCode));
	}

	audioBackend.SetupSoloudSettings(m_SoloudEngine);

	// Quad asset
	InitQuad();
}

void AssetManager::Terminate()
{
	// Quad asset
	TerminateQuad();

	// SoLoud
	AudioBackend& audioBackend = AudioBackend::Get();
	audioBackend.TerminateSoloud(m_SoloudEngine);
	m_SoloudEngine = nullptr;
}

void AssetManager::InitQuad()
{
	// clang-format off

    constexpr f32 vertices[] = {
        // Positions     // Tex Coords
        -0.5f, -0.5f,    0.0f, 0.0f,    // Bottom Left
         0.5f, -0.5f,    1.0f, 0.0f,    // Bottom Right
        -0.5f,  0.5f,    0.0f, 1.0f,    // Top Left
         0.5f,  0.5f,    1.0f, 1.0f     // Top Right
    };

    constexpr u32 indices[] = {
        0, 1, 2, // Bottom Left Triangle
        1, 3, 2  // Top Right Triangle
    };

	// clang-format on

	RenderBackend& renderBackend = RenderBackend::Get();

	renderBackend.GenerateVertexArray(m_QuadVao);

	renderBackend.GenerateBuffer(m_QuadVbo, BufferType::ArrayBuffer);
	renderBackend.SetBufferData(m_QuadVbo, BufferType::ArrayBuffer, BufferDrawType::StaticDraw, sizeof(vertices), vertices);

	renderBackend.GenerateBuffer(m_QuadEbo, BufferType::ElementArrayBuffer);
	renderBackend.SetBufferData(m_QuadEbo, BufferType::ElementArrayBuffer, BufferDrawType::StaticDraw, sizeof(indices), indices);

	SetupQuadVertexAttributes();

	renderBackend.UnbindVertexArray();
}

void AssetManager::SetupQuadVertexAttributes() const
{
	RenderBackend& renderBackend = RenderBackend::Get();
	renderBackend.SetVertexAttributePointer(0, 2, VertexAttributeDataType::F32, false, 4 * sizeof(f32), 0);
	renderBackend.SetVertexAttributePointer(1, 2, VertexAttributeDataType::F32, false, 4 * sizeof(f32), 2 * sizeof(f32));
}

void AssetManager::TerminateQuad()
{
	RenderBackend& renderBackend = RenderBackend::Get();

	renderBackend.DeleteBuffer(m_QuadVbo);
	m_QuadVbo = 0;

	renderBackend.DeleteBuffer(m_QuadEbo);
	m_QuadEbo = 0;

	renderBackend.DeleteVertexArray(m_QuadVao);
	m_QuadVao = 0;
}

u32 AssetManager::GetQuadVao() const
{
	return m_QuadVao;
}

u32 AssetManager::GetQuadVbo() const
{
	return m_QuadVbo;
}

u32 AssetManager::GetQuadEbo() const
{
	return m_QuadEbo;
}

SharedPtr<Texture> AssetManager::LoadTexture(const std::string& filePath, const TextureParameters& parameters)
{
	PREPARE_ASSET_FACTORY_CONSTRUCTOR(Texture);

	Texture* instance = new Texture(filePath);

	ASSERT_POST_ASSET_FACTORY_CONSTRUCTOR(Texture);

	instance->Init(parameters);

	return instance;
}

SharedPtr<TextureSlice> AssetManager::CreateTextureSlice(SharedPtr<Texture> texture, const i32 index)
{
	PREPARE_ASSET_FACTORY_CONSTRUCTOR(TextureSlice);

	SharedPtr<TextureSlice> instance = new TextureSlice(std::move(texture), index);

	ASSERT_POST_ASSET_FACTORY_CONSTRUCTOR(TextureSlice);

	return instance;
}

SharedPtr<Animation> AssetManager::CreateAnimation()
{
	PREPARE_ASSET_FACTORY_CONSTRUCTOR(Animation);

	Animation* instance = new Animation();

	ASSERT_POST_ASSET_FACTORY_CONSTRUCTOR(Animation);

	return instance;
}

SharedPtr<AnimationFrame> AssetManager::CreateAnimationFrame(Animation* animation, SharedPtr<Sprite> sprite, const f32 duration)
{
	PREPARE_ASSET_FACTORY_CONSTRUCTOR(AnimationFrame);

	SharedPtr<AnimationFrame> instance = new AnimationFrame(animation, std::move(sprite), duration);

	ASSERT_POST_ASSET_FACTORY_CONSTRUCTOR(AnimationFrame);

	return instance;
}

SharedPtr<AnimationSprite> AssetManager::CreateAnimationSprite()
{
	PREPARE_ASSET_FACTORY_CONSTRUCTOR(AnimationSprite);

	SharedPtr<AnimationSprite> instance = new AnimationSprite();

	ASSERT_POST_ASSET_FACTORY_CONSTRUCTOR(AnimationSprite);

	return instance;
}

SharedPtr<Audio> AssetManager::LoadAudio(const std::string& filePath, const bool stream)
{
	PREPARE_ASSET_FACTORY_CONSTRUCTOR(Audio);

	Audio* instance = new Audio(filePath, stream);

	ASSERT_POST_ASSET_FACTORY_CONSTRUCTOR(Audio);

	return instance;
}

void AssetManager::UnloadMaterialUniforms(const Material* material)
{
	for (const auto uniform : material->m_ValidUniforms)
	{
		PREPARE_ASSET_FACTORY_DESTRUCTOR();

		delete uniform;

		ASSERT_POST_ASSET_FACTORY_DESTRUCTOR();
	}

	for (const auto uniform : material->m_InvalidUniforms)
	{
		PREPARE_ASSET_FACTORY_DESTRUCTOR();

		delete uniform;

		ASSERT_POST_ASSET_FACTORY_DESTRUCTOR();
	}
}

Shader* AssetManager::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	const auto newShader = new Shader(vertexShaderPath, fragmentShaderPath);
	const auto it = m_Shaders.find(newShader);

	if (it == m_Shaders.end())
	{
		try
		{
			newShader->Init();
		}
		catch (const std::exception&)
		{
			delete newShader;
			throw;
		}

		m_Shaders[newShader] = 1;
		return newShader;
	}

	m_Shaders[it->first] = it->second + 1;
	delete newShader;
	return it->first;
}

void AssetManager::UnloadShader(Shader* shader)
{
	const auto it = m_Shaders.find(shader);

	if (it->second == 1)
	{
		it->first->Free();
		m_Shaders.erase(it);
		delete shader;
		return;
	}

	m_Shaders[shader] = it->second - 1;
}

// NOLINTEND(CppMemberFunctionMayBeStatic)
