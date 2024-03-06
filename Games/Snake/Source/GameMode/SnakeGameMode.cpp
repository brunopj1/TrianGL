#include "SnakeGameMode.h"

#include "Entities/FoodEntity.h"
#include "Entities/SnakeEntity.h"
#include "Core/EntityManager.h"
#include "Entities/Camera.h"
#include "Components/TextureRenderer.h"
#include "Core/ResourceManager.h"
#include "Resources/TestMaterial.h"

using namespace Engine::Core;

void SnakeGameMode::OnStart()
{
    const auto camera = EntityManager::SpawnEntity<Engine::Entities::Camera>();
    camera->SetAsMainCamera();

    const auto snake = EntityManager::SpawnEntity<SnakeEntity>();

    const auto food1 = EntityManager::SpawnEntity<FoodEntity>();

    const auto food2 = EntityManager::SpawnEntity<FoodEntity>();
}
