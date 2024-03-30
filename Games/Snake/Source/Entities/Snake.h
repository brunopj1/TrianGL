#pragma once

#include "AudioManager.h"
#include "Grid.h"
#include "SnakeBody.h"
#include "Game/Entity.h"
#include "Resources/Texture.h"

class Snake final : public TGL::Entity
{
private:
    glm::ivec2 m_BodyDirection;
    glm::ivec2 m_MoveDirection;

    std::vector<SnakeBody*> m_Body;

private:
    std::shared_ptr<TGL::Texture> m_SpriteSheet;

public:
    Snake(Grid* grid, std::shared_ptr<TGL::Texture> spriteSheet, const glm::ivec2& position, const glm::ivec2& direction);
    ~Snake() override = default;

protected:
    void OnUpdate(float deltaTime) override;

public:
    void Move(Grid* grid, AudioManager* audioManager); // Returns true if the apple was eaten

private:
    void SpawnHead(Grid* grid, const glm::ivec2& position);

    void DestroyTailEnd(Grid* grid);
    void DestroyTail(Grid* grid, const SnakeBody* firstBody);

    void UpdateTail() const;
};
