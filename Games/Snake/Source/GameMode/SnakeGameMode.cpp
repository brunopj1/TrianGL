#include "SnakeGameMode.h"

#include "Entities/FoodEntity.h"
#include "Entities/SnakeEntity.h"
#include "Core/EntityManager.h"

void SnakeGameMode::OnStart()
{
    const auto em = Engine::Core::EntityManager::GetInstance();

    auto food1 = em->CreateEntity<FoodEntity>();

    auto snake = em->CreateEntity<SnakeEntity>();

    auto food2 = em->CreateEntity<FoodEntity>();
}
