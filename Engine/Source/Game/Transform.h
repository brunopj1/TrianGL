#pragma once

#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"

namespace Engine
{
    class Transform
    {
    private:
        friend class TextureRenderer;

    private:
        glm::vec2 m_Position = {0.0f, 0.0f};
        float m_Rotation = 0.0f;
        glm::vec2 m_Scale = {1.0f, 1.0f};

        glm::mat4 m_TransformMatrix = glm::mat4(1.0f);

        bool m_WasModified = false;

    public:
        Transform() = default;
        ~Transform() = default;

    public:
        glm::vec2 GetPosition() const;
        float GetRotationRad() const;
        float GetRotationDeg() const;
        glm::vec2 GetScale() const;

    public:
        void SetPosition(const glm::vec2& newPosition);
        void SetRotationRag(float newRotation);
        void SetRotationDeg(float newRotation);
        void SetScale(const glm::vec2& newScale);
        void SetScale(float newScale);

    public:
        void TranslateBy(const glm::vec2& translation);
        void RotateByRad(float rotation);
        void RotateByDeg(float rotation);
        void ScaleBy(const glm::vec2& scale);
        void ScaleBy(float scale);

    private:
        glm::mat4 GetTransformMatrix();
    };
}
