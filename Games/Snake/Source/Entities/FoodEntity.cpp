#include "FoodEntity.h"

#include "OrderOfExecution.hpp"
#include <iostream>

FoodEntity::FoodEntity()
    : Entity(false)
{}

int FoodEntity::GetOrderOfExecution() const
{
    return static_cast<int>(OrderOfExecution::Food);
}

void FoodEntity::OnStart()
{
    std::cout << "I am food\n";
}
