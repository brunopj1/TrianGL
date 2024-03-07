#include "FoodEntity.h"

#include "Components/TextureRenderer.h"
#include "Services/EntityManager.h"
#include "GameMode/OrderOfExecution.hpp"
#include <iostream>

FoodEntity::FoodEntity()
    : Entity(false)
{
    const auto foodTexture = Engine::Services::EntityManager::AttachComponent<Engine::Components::TextureRenderer>(this);
    const auto material = foodTexture->UseDefaultMaterial();
}

int FoodEntity::GetOrderOfExecution() const
{
    return static_cast<int>(OrderOfExecution::Food);
}

void FoodEntity::OnStart()
{
    std::cout << "I am food\n";
}
