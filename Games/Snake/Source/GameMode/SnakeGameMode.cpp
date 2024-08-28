#include "SnakeGameMode.h"

#include "Entities/Apple.h"
#include "Entities/Snake.h"
#include "Implementations/Entities/Camera.h"
#include "Implementations/Components/SpriteRenderer.h"
#include "Core/InputSystem.h"
#include "Core/Window.h"
#include "Assets/Material.h"

#ifdef IMGUI
#include <imgui.h>
#include <imgui_stdlib.h>
#endif

using namespace TGL;

// TODO add a more fluid motion to the snake

SnakeGameMode::SnakeGameMode()
{
    SpawnEntity<Camera>(true);

    auto textureParams = TextureParameters();
    textureParams.Filter = TextureFilterMode::Nearest;
    textureParams.GenerateMipmaps = false;

    m_SpriteSheet = Texture::Load("Assets/Textures/sprite_sheet.png", textureParams);
    m_SpriteSheet->CreateSliceGrid({25, 25});

    m_TickRate = m_TickTimer = 0.25f;

    m_Grid = SpawnEntity<Grid>(m_SpriteSheet, glm::uvec2(5));

    m_Snake = SpawnEntity<Snake>(m_Grid, m_SpriteSheet, glm::ivec2(2, 2), glm::ivec2(0, 1));

    m_Apple = SpawnEntity<Apple>(m_Grid, m_SpriteSheet);

    m_AudioManager = SpawnEntity<AudioManager>();

    m_ParticleEmitter = SpawnEntity<ParticleEmitter>();

    m_Grid->FocusCamera();

    Camera::GetMainCamera()->SetBackgroundColor({0.07, 0.59, 0.85});
}

void SnakeGameMode::OnEarlyUpdate(const f32 deltaTime)
{
#ifdef IMGUI
    RenderImGui();
#endif
}

void SnakeGameMode::OnLateUpdate(const f32 deltaTime)
{
    if (m_Victory)
    {
        return;
    }

    m_TickTimer -= deltaTime;

    if (m_TickTimer <= 0)
    {
        m_TickTimer = m_TickRate;

        m_Snake->Move(m_Grid, m_AudioManager, m_ParticleEmitter);

        if (!m_Apple.IsValid())
        {
            m_Victory = true;
        }
    }
}

void SnakeGameMode::OnWindowResized(glm::uvec2 newResolution)
{
    m_Grid->FocusCamera();
}

void SnakeGameMode::RenderImGui()
{
#ifdef IMGUI
    static std::string test = "Hello world!";
    
    ImGui::SetNextWindowPos({10, 10}, ImGuiCond_Appearing);
    ImGui::SetNextWindowSize({250, 200}, ImGuiCond_Appearing);

    if (ImGui::Begin("Settings"))
    {
        ImGui::SliderFloat("Tick rate", &m_TickRate, 0.1f, 1.0f);

        ImGui::Separator();

        if (ImGui::Button("Randomize apple"))
        {
            Apple* apple = m_Apple.Get();

            if (apple != nullptr)
            {
                apple->RandomizePosition(m_Grid);
            }
        }

        ImGui::InputText("Test", &test);
    }

    ImGui::End();
#endif
}
