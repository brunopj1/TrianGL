#pragma once

#include "AudioManager.h"
#include "Grid.h"
#include "ParticleEmitter.h"
#include "SnakeBody.h"
#include "Game/Entity.h"
#include "Assets/Texture.h"

class Snake final : public TGL::Entity
{
private:
    glm::ivec2 m_BodyDirection;
    glm::ivec2 m_MoveDirection;

    std::vector<SnakeBody*> m_Body;

private:
    TGL::SharedPtr<TGL::Texture> m_SpriteSheet;

public:
    Snake(Grid* grid, TGL::SharedPtr<TGL::Texture> spriteSheet, const glm::ivec2& position, const glm::ivec2& direction);
    ~Snake() override = default;

protected:
    void OnUpdate(f32 deltaTime) override;

public:
    void Move(Grid* grid, AudioManager* audioManager, ParticleEmitter* particleEmitter); // Returns true if the apple was eaten

private:
    void SpawnHead(Grid* grid, const glm::ivec2& position);

    void DestroyTailEnd(Grid* grid);
    void DestroyTail(Grid* grid, const SnakeBody* firstBody);

    void UpdateTail() const;
};
