#include "Camera.h"

#include "Core/Window.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <stdexcept>

using namespace Engine::Entities;

Camera::Camera(const bool setAsMainCamera)
    : Entity(false)
{
    m_AspectRatio = Core::Window::GetAspectRatio();

    if (setAsMainCamera)
    {
        SetAsMainCamera();
    }
}

Camera::~Camera()
{
    if (s_MainCamera == this)
    {
        s_MainCamera = nullptr;
    }
}

Camera* Camera::GetMainCamera()
{
    return s_MainCamera;
}

void Camera::SetAsMainCamera()
{
    s_MainCamera = this;
}

float Camera::GetHorizontalSize() const
{
    return m_HorizontalSize;
}

void Camera::SetHorizontalSize(const float size, const bool lock)
{
    if (size <= 0.0f)
    {
        throw std::invalid_argument("The size must be greater than 0");
    }

    m_HorizontalSize = size;
    if (lock) m_LockHorizontalSize = true;
}

float Camera::GetVerticalSize() const
{
    return m_HorizontalSize / m_AspectRatio;
}

void Camera::SetVerticalSize(const float size, const bool lock)
{
    if (size <= 0.0f)
    {
        throw std::invalid_argument("The size must be greater than 0");
    }

    m_HorizontalSize = size * m_AspectRatio;
    if (lock) m_LockHorizontalSize = false;
}

bool Camera::IsSizeLockedHorizontally() const
{
    return m_LockHorizontalSize;
}

void Camera::SetAspectRatio(const float aspectRatio)
{
    if (aspectRatio <= 0.0f)
    {
        throw std::invalid_argument("The aspect ratio must be greater than 0");
    }

    m_AspectRatio = aspectRatio;
}

glm::vec3 Camera::GetBackgroundColor() const
{
    return m_BackgroundColor;
}

void Camera::SetBackgroundColor(const glm::vec3& color)
{
    m_BackgroundColor = color;
}

glm::mat4 Camera::GetViewMatrix() const
{
    const glm::vec3 position = glm::vec3(GetTransform().GetPosition(), 1.0f);
    constexpr glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    constexpr glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    return lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    const float halfSizeH = m_HorizontalSize / 2.0f;
    const float halfSizeV = halfSizeH / m_AspectRatio;
    return glm::ortho(-halfSizeH, halfSizeH, -halfSizeV, halfSizeV, 0.1f, 100.0f);
}

glm::mat4 Camera::GetProjectionViewMatrix() const
{
    return GetProjectionMatrix() * GetViewMatrix();
}
