#include "Renderable.h"

using namespace Engine::Game::Internal;

Engine::Game::Transform& Renderable::GetTransform()
{
    return m_Transform;
}

const Engine::Game::Transform& Renderable::GetTransform() const
{
    return m_Transform;
}
