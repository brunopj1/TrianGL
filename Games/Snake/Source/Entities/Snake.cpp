#include "Snake.h"

#include "Apple.h"
#include "Core/Services/Public/InputSystem.h"
#include "Implementations/Materials/DefaultSpriteMaterial.h"
#include <utility>

using namespace TGL;

Snake::Snake(Grid* grid, SharedPtr<Texture> spriteSheet, const glm::ivec2& position, const glm::ivec2& direction)
	: Entity(true), m_SpriteSheet(std::move(spriteSheet))
{
	m_BodyDirection = m_MoveDirection = direction;

	SpawnHead(grid, position - direction);
	SpawnHead(grid, position);
}

void Snake::OnUpdate(const f32 deltaTime)
{
	const InputSystem& inputSystem = InputSystem::Get();

	glm::ivec2 direction = {0, 0};

	if (inputSystem.IsKeyDown(KeyCode::W))
	{
		direction = {0, 1};
	}
	if (inputSystem.IsKeyDown(KeyCode::S))
	{
		direction = {0, -1};
	}
	if (inputSystem.IsKeyDown(KeyCode::A))
	{
		direction = {-1, 0};
	}
	if (inputSystem.IsKeyDown(KeyCode::D))
	{
		direction = {1, 0};
	}

	if (direction != glm::ivec2(0) && direction != m_MoveDirection && direction != -m_BodyDirection)
	{
		m_MoveDirection = direction;
		m_Body.front()->SetAsHead(m_MoveDirection);
	}
}

void Snake::Move(Grid* grid, AudioManager* audioManager, ParticleEmitter* particleEmitter)
{
	const glm::uvec2 gridSize = grid->GetSize();
	const glm::ivec2 headPosition = m_Body.front()->GetTransform().GetPosition();

	glm::ivec2 nextPosition = headPosition + m_MoveDirection;
	nextPosition.x = (nextPosition.x + gridSize.x) % gridSize.x;
	nextPosition.y = (nextPosition.y + gridSize.y) % gridSize.y;

	Entity* hitEntity = grid->GetCell(nextPosition);

	// No hit
	if (hitEntity == nullptr || hitEntity == m_Body.back())
	{
		DestroyTailEnd(grid);
		SpawnHead(grid, nextPosition);
		UpdateTail();
		audioManager->PlayMoveAudio();
	}
	// Hit snake
	else if (const SnakeBody* hitBody = CastTo<SnakeBody>(hitEntity); hitBody != nullptr)
	{
		DestroyTail(grid, hitBody);
		SpawnHead(grid, nextPosition);
		UpdateTail();
		audioManager->PlayHurtAudio();
		particleEmitter->Emit(nextPosition, ParticleType::Damage);
	}
	// Hit apple
	else if (Apple* hitApple = CastTo<Apple>(hitEntity); hitApple != nullptr)
	{
		SpawnHead(grid, nextPosition);
		hitApple->RandomizePosition(grid);
		audioManager->PlayAppleAudio();
		particleEmitter->Emit(nextPosition, ParticleType::Grow);
	}

	m_BodyDirection = m_MoveDirection;
}

void Snake::SpawnHead(Grid* grid, const glm::ivec2& position)
{
	const auto snakeBody = SpawnEntity<SnakeBody>(grid, m_SpriteSheet, position, m_MoveDirection);
	m_Body.insert(m_Body.begin(), snakeBody);

	if (const auto bodySize = m_Body.size(); bodySize > 1)
	{
		if (bodySize == 2)
		{
			m_Body[1]->SetAsTail();
		}
		else
		{
			m_Body[1]->SetAsBody();
		}
	}
}

void Snake::DestroyTailEnd(Grid* grid)
{
	SnakeBody* body = m_Body.back();
	m_Body.pop_back();

	grid->SetCell(body->GetTransform().GetPosition(), nullptr);
	body->Destroy();
}

void Snake::DestroyTail(Grid* grid, const SnakeBody* firstBody)
{
	while (true)
	{
		SnakeBody* body = m_Body.back();
		m_Body.pop_back();

		grid->SetCell(body->GetTransform().GetPosition(), nullptr);
		body->Destroy();

		if (body == firstBody)
		{
			break;
		}
	}
}

void Snake::UpdateTail() const
{
	m_Body.back()->SetAsTail();
}
