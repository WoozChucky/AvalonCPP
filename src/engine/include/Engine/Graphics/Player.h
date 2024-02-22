#pragma once

#include "Entity.h"

class Player : public Entity {
public:
    Player(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, F32 speed) : Entity(TexturesName::Player, position, size, velocity, speed) { }
    ~Player() = default;

    void Update(F32 deltaTime) override {
        Position += Velocity * Speed * deltaTime;
    }

    void Draw(SpriteBatch& spriteBatch) override {
        glm::vec4 destRect(Position.x, Position.y, Size.x, Size.y);
        glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

        spriteBatch.Draw(destRect, uvRect, Texture.Id, 0.0f, Color);
    }
};
