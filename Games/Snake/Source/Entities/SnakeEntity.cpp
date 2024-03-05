#include "SnakeEntity.h"

#include "Core/InputSystem.h"
#include "Core/Window.h"
#include "GameMode/OrderOfExecution.hpp"
#include <iostream>

SnakeEntity::SnakeEntity()
    : Entity(true)
{}

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
