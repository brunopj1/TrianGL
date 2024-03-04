#include "SnakeEntity.h"

#include "Core/InputSystem.h"
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
{}
