#include "Apple.h"

#include "Components/TextureRenderer.h"
#include "DefaultResources/DefaultMaterial.h"
#include "Services/EntityManager.h"
#include "GameMode/OrderOfExecution.hpp"
#include <iostream>

Apple::Apple()
    : Entity(false)
{
    const auto foodTexture = Engine::Services::EntityManager::AttachComponent<Engine::Components::TextureRenderer>(this);
    const auto material = foodTexture->UseDefaultMaterial();
    material->GetColorAttr()->SetValue({0.9f, 0.23f, 0.15f, 1.0f});
}

int Apple::GetOrderOfExecution() const
{
    return static_cast<int>(OrderOfExecution::Food);
}
