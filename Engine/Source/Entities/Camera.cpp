#include "Camera.h"

#include "Core/Window.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <stdexcept>

using namespace TGL;

#define CAMERA_DEPTH 2000.0f

Camera::Camera(const bool setAsMainCamera)
    : Entity(false)
{
    m_AspectRatio = Window::GetAspectRatio();

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

glm::vec2 Camera::GetSize() const
{
    return {m_HorizontalSize, m_HorizontalSize / m_AspectRatio};
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

void Camera::LockSize(const bool horizontally)
{
    m_LockHorizontalSize = horizontally;
}

bool Camera::IsSizeLockedHorizontally() const
{
    return m_LockHorizontalSize;
}

float Camera::GetAspectRatio() const
{
    return m_AspectRatio;
}

glm::vec3 Camera::GetBackgroundColor() const
{
    return m_BackgroundColor;
}

void Camera::SetBackgroundColor(const glm::vec3& color)
{
    m_BackgroundColor = color;
}

void Camera::SetAspectRatio(const float aspectRatio)
{
    if (aspectRatio <= 0.0f)
    {
        throw std::invalid_argument("The aspect ratio must be greater than 0");
    }

    m_AspectRatio = aspectRatio;
}

void Camera::UpdateMatrices()
{
    const auto transform = GetTransform();

    // View matrix
    const glm::vec3 position = glm::vec3(transform.GetPosition(), CAMERA_DEPTH * 0.5f);
    const glm::vec3 up = glm::vec3(glm::sin(transform.GetRotationRad()), glm::cos(transform.GetRotationRad()), 0.0f);
    constexpr glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

    m_ViewMatrix = lookAt(position, position + front, up);

    // Projection matrix
    const float halfSizeH = m_HorizontalSize / 2.0f;
    const float halfSizeV = halfSizeH / m_AspectRatio;

    m_ProjectionMatrix = glm::ortho(-halfSizeH, halfSizeH, -halfSizeV, halfSizeV, 0.0f, CAMERA_DEPTH);

    // Projection view matrix
    m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

const glm::mat4& Camera::GetViewMatrix() const
{
    return m_ViewMatrix;
}

const glm::mat4& Camera::GetProjectionMatrix() const
{
    return m_ProjectionMatrix;
}

const glm::mat4& Camera::GetProjectionViewMatrix() const
{
    return m_ProjectionViewMatrix;
}
