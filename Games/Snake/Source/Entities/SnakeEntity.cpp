#include "SnakeEntity.h"

#include "OrderOfExecution.hpp"
#include <iostream>

SnakeEntity::SnakeEntity()
    : Entity(false)
{}

int SnakeEntity::GetOrderOfExecution() const
{
    return static_cast<int>(OrderOfExecution::Snake);
}

void SnakeEntity::OnStart()
{
    std::cout << "I am the snake\n";
}
