﻿#include <Implementations/Entities/Camera.h>

#include <Core/Window.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <stdexcept>

using namespace TGL;

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

void Camera::SetDepthRange(int min, int max)
{
    if (max <= min)
    {
        throw std::invalid_argument("The maximum depth must be greater than the minimum depth");
    }

    m_DepthRange = {min, max};
}

glm::vec2 Camera::GetDepthRange() const
{
    return m_DepthRange;
}

glm::vec3 Camera::GetBackgroundColor() const
{
    return m_BackgroundColor;
}

void Camera::SetBackgroundColor(const glm::vec3& color)
{
    m_BackgroundColor = color;
}

glm::vec2 Camera::ScreenToWorldPosition(const glm::vec2& screenPos) const
{
    const glm::uvec2 screenResolution = Window::GetResolution();

    const glm::vec4 clipPos = {
        screenPos.x / screenResolution.x * 2.0f - 1.0f,
        1.0f - screenPos.y / screenResolution.y * 2.0f,
        0.0f, 1.0f
    };

    const glm::mat4 inverseProjectionViewMatrix = ComputeProjectionViewMatrix(true);

    glm::vec4 worldPos = inverseProjectionViewMatrix * clipPos;
    worldPos /= worldPos.w;

    return worldPos;
}

glm::vec2 Camera::WorldToScreenPosition(const glm::vec2& worldPos) const
{
    const glm::mat4 projectionViewMatrix = ComputeProjectionViewMatrix();

    const glm::vec4 clipPos = projectionViewMatrix * glm::vec4(worldPos, 0.0f, 1.0f);

    const glm::vec2 screenPos = {
        (clipPos.x + 1.0f) / 2.0f * Window::GetResolution().x,
        (1.0f - clipPos.y) / 2.0f * Window::GetResolution().y
    };

    return screenPos;
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
    m_ViewMatrix = ComputeViewMatrix();
    m_ProjectionMatrix = ComputeProjectionMatrix();
    m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

glm::mat4 Camera::ComputeViewMatrix() const
{
    const auto transform = GetTransform();

    const glm::vec3 position = glm::vec3(transform.GetPosition(), m_DepthRange.y * 0.5f);
    const glm::vec3 up = glm::vec3(glm::sin(transform.GetRotationRad()), glm::cos(transform.GetRotationRad()), 0.0f);
    constexpr glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

    return lookAt(position, position + front, up);
}

glm::mat4 Camera::ComputeProjectionMatrix() const
{
    const float halfSizeH = m_HorizontalSize / 2.0f;
    const float halfSizeV = halfSizeH / m_AspectRatio;
    const float farPlane = static_cast<float>(m_DepthRange.y - m_DepthRange.x);

    return glm::ortho(-halfSizeH, halfSizeH, -halfSizeV, halfSizeV, 0.0f, farPlane);
}

glm::mat4 Camera::ComputeProjectionViewMatrix(const bool inverse) const
{
    const glm::mat4 projectionMatrix = ComputeProjectionMatrix();
    const glm::mat4 viewMatrix = ComputeViewMatrix();
    const glm::mat4 projectionViewMatrix = projectionMatrix * viewMatrix;

    return inverse ? glm::inverse(projectionViewMatrix) : projectionViewMatrix;
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
