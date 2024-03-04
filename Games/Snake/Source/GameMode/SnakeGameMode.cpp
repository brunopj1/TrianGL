#include "SnakeGameMode.h"

#include "Entities/FoodEntity.h"
#include "Entities/SnakeEntity.h"
#include "Core/EntityManager.h"
#include "Entities/Camera.h"
#include "Components/TextureRenderer.h"


void SnakeGameMode::OnStart()
{
    const auto em = Engine::Core::EntityManager::GetInstance();

    auto camera = em->SpawnEntity<Engine::Entities::Camera>();
    camera->SetAsMainCamera();

    auto snake = em->SpawnEntity<SnakeEntity>();

    auto food1 = em->SpawnEntity<FoodEntity>();

    auto food2 = em->SpawnEntity<FoodEntity>();

    auto snakeTexture = em->AttachComponent<Engine::Components::TextureRenderer>(snake);
    snake->GetTransform().SetPosition({2, 0});
    snake->GetTransform().SetRotationDeg(45);
    snake->GetTransform().SetScale(1.5);
}
