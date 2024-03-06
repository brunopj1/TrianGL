#include "SnakeEntity.h"

#include "Components/TextureRenderer.h"
#include "Core/EntityManager.h"
#include "Core/InputSystem.h"
#include "Core/ResourceManager.h"
#include "Core/Window.h"
#include "DefaultResources/DefaultMaterial.h"
#include "GameMode/OrderOfExecution.hpp"
#include "Resources/TextureParameters.hpp"
#include <iostream>

// TODO move the services to Engine::Services

SnakeEntity::SnakeEntity()
    : Entity(true)
{
    GetTransform().SetPosition({2, 0});
    GetTransform().SetRotationDeg(45);
    GetTransform().SetScale(1.5);

    Engine::Resources::TextureParameters parameters;
    parameters.Filter = Engine::Resources::TextureFilterMode::Nearest;
    const auto texture = Engine::Core::ResourceManager::LoadTexture("Assets/Textures/ugly_smile.png", parameters);

    const auto snakeTexture = Engine::Core::EntityManager::AttachComponent<Engine::Components::TextureRenderer>(this);
    const auto material = snakeTexture->UseDefaultMaterial();
    material->GetTextureAttr()->SetValue(texture);
}

int SnakeEntity::GetOrderOfExecution() const
{
    return static_cast<int>(OrderOfExecution::Snake);
}

void SnakeEntity::OnStart()
{
    std::cout << "I am the snake\n";
}

void SnakeEntity::OnUpdate()
{
    if (Engine::Core::InputSystem::WasKeyPressed(Engine::Core::KeyCode::Num1))
    {
        Engine::Core::Window::SetFullscreen(false);
        Engine::Core::Window::SetPosition({50, 50});
        Engine::Core::Window::SetResolution({1280, 720});
    }
    else if (Engine::Core::InputSystem::WasKeyPressed(Engine::Core::KeyCode::Num2))
    {
        Engine::Core::Window::SetPosition({0, 0});
        Engine::Core::Window::SetResolution({1920, 1080});
        Engine::Core::Window::SetFullscreen(true);
    }
}
