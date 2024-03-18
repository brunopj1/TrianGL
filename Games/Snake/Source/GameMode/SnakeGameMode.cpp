#include "SnakeGameMode.h"

#include "Entities/Apple.h"
#include "Entities/Snake.h"
#include "Entities/Camera.h"
#include "Components/TextureRenderer.h"
#include "Core/Window.h"
#include "Resources/Material.h"

using namespace TGL;

// TODO disable the loop around mechanic
// TODO add imgui overlay to control the game
// TODO add a more fluid motion to the snake

// TODO grid edge is inconsistent
// TODO snake texture sometimes has weird bugs

SnakeGameMode::SnakeGameMode()
{
    m_Camera = SpawnEntity<Camera>(true);
    m_WindowSize = {0, 0}; // Force the camera to focus on the grid

    auto textureParams = TextureParameters();
    textureParams.Filter = TextureFilterMode::Nearest;

    m_SpriteSheet = Texture::Load("Assets/Textures/sprite_sheet.png", textureParams);
    m_SpriteSheet->CreateSliceGrid({25, 25});

    m_TickRate = m_TickTimer = 0.35f;

    m_Grid = SpawnEntity<Grid>(glm::uvec2(10, 10));

    m_Snake = SpawnEntity<Snake>(m_Grid, m_SpriteSheet, glm::ivec2(2, 2), glm::ivec2(0, 1));

    m_Apple = SpawnEntity<Apple>(m_Grid, m_SpriteSheet);
}

void SnakeGameMode::OnEarlyUpdate(const float deltaTime)
{
    const glm::uvec2 currentWindowSize = Window::GetResolution();

    if (currentWindowSize != m_WindowSize)
    {
        m_Grid->FocusCamera();
    }

    m_WindowSize = currentWindowSize;
}

void SnakeGameMode::OnLateUpdate(const float deltaTime)
{
    m_TickTimer -= deltaTime;

    if (m_TickTimer <= 0)
    {
        m_TickTimer = m_TickRate;

        m_Snake->Move(m_Grid);
    }
}
