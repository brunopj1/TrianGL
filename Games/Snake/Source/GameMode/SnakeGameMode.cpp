#include "SnakeGameMode.h"

#include "Entities/FoodEntity.h"
#include "Entities/SnakeEntity.h"
#include "Services/EntityManager.h"
#include "Entities/Camera.h"

using namespace Engine::Services;

void SnakeGameMode::OnStart()
{
    const auto camera = EntityManager::SpawnEntity<Engine::Entities::Camera>(true);

    const auto snake = EntityManager::SpawnEntity<SnakeEntity>();

    const auto food1 = EntityManager::SpawnEntity<FoodEntity>();

    const auto food2 = EntityManager::SpawnEntity<FoodEntity>();
}
