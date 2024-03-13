#include "SnakeGameMode.h"

#include "Entities/Apple.h"
#include "Entities/Snake.h"
#include "Entities/Camera.h"
#include "Components/TextureRenderer.h"
#include "Core/Window.h"

using namespace TGL;

// TODO disable the loop around mechanic

SnakeGameMode::SnakeGameMode()
{
    m_Camera = SpawnEntity<Camera>(true);
    m_WindowSize = Window::GetResolution();

    m_Grid = SpawnEntity<Grid>(glm::uvec2(3, 3));

    m_Snake = SpawnEntity<Snake>(m_Grid, glm::ivec2(1, 1), glm::ivec2(0, 1));

    m_Apple = SpawnEntity<Apple>(m_Grid);

    FocusCameraOnGrid();
}

void SnakeGameMode::OnEarlyUpdate(const float deltaTime)
{
    const glm::uvec2 currentWindowSize = Window::GetResolution();

    if (currentWindowSize != m_WindowSize)
    {
        FocusCameraOnGrid();
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

void SnakeGameMode::FocusCameraOnGrid() const
{
    const float aspectRatio = m_Camera->GetAspectRatio();
    const glm::uvec2 gridSize = m_Grid->GetSize();

    if (aspectRatio > 1)
    {
        m_Camera->SetVerticalSize(gridSize.y + 0.5f);
    }
    else
    {
        m_Camera->SetHorizontalSize(gridSize.x + 0.5f);
    }

    m_Camera->GetTransform().SetPosition(glm::vec3(gridSize, 0) * 0.5f);
}
