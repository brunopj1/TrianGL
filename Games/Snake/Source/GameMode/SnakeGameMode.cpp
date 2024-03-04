#include "SnakeGameMode.h"

#include "Entities/FoodEntity.h"
#include "Entities/SnakeEntity.h"
#include "Core/EntityManager.h"
#include "Entities/Camera.h"
#include "Components/TextureRenderer.h"

using namespace Engine::Core;

void SnakeGameMode::OnStart()
{
    auto camera = EntityManager::SpawnEntity<Engine::Entities::Camera>();
    camera->SetAsMainCamera();

    auto snake = EntityManager::SpawnEntity<SnakeEntity>();

    auto food1 = EntityManager::SpawnEntity<FoodEntity>();

    auto food2 = EntityManager::SpawnEntity<FoodEntity>();

    auto snakeTexture = EntityManager::AttachComponent<Engine::Components::TextureRenderer>(snake);
    snake->GetTransform().SetPosition({2, 0});
    snake->GetTransform().SetRotationDeg(45);
    snake->GetTransform().SetScale(1.5);
}
