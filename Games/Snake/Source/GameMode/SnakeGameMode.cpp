#include "SnakeGameMode.h"

#include "Entities/Apple.h"
#include "Entities/Snake.h"
#include "Implementations/Entities/Camera.h"
#include "Implementations/Components/SpriteRenderer.h"
#include "Core/InputSystem.h"
#include "Core/Window.h"
#include "Resources/Material.h"

#ifdef DEBUG
#include <imgui.h>
#endif

using namespace TGL;

// TODO add a more fluid motion to the snake

SnakeGameMode::SnakeGameMode()
{
    m_Camera = SpawnEntity<Camera>(true);
    m_WindowSize = {0, 0}; // Force the camera to focus on the grid

    auto textureParams = TextureParameters();
    textureParams.Filter = TextureFilterMode::Nearest;
    textureParams.GenerateMipmaps = false;

    m_SpriteSheet = Texture::Load("Assets/Textures/sprite_sheet.png", textureParams);
    m_SpriteSheet->CreateSliceGrid({25, 25});

    m_TickRate = m_TickTimer = 0.25f;

    m_Grid = SpawnEntity<Grid>(glm::uvec2(15));

    m_Snake = SpawnEntity<Snake>(m_Grid, m_SpriteSheet, glm::ivec2(2, 2), glm::ivec2(0, 1));

    m_Apple = SpawnEntity<Apple>(m_Grid, m_SpriteSheet);
}

void SnakeGameMode::OnEarlyUpdate(const float deltaTime)
{
#ifdef DEBUG
    RenderImGui();
#endif

    const glm::uvec2 currentWindowSize = Window::GetResolution();

    if (currentWindowSize != m_WindowSize)
    {
        m_Grid->FocusCamera();
    }

    m_WindowSize = currentWindowSize;
}

void SnakeGameMode::OnLateUpdate(const float deltaTime)
{
    if (m_Victory)
    {
        return;
    }

    m_TickTimer -= deltaTime;

    if (m_TickTimer <= 0)
    {
        m_TickTimer = m_TickRate;

        m_Snake->Move(m_Grid);

        if (m_Apple.Get() == nullptr)
        {
            m_Victory = true;
        }
    }
}

#ifdef DEBUG

void SnakeGameMode::RenderImGui()
{
    ImGui::SetNextWindowSize({300, 200}, ImGuiCond_Appearing);

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
    }

    ImGui::End();
}

#endif
