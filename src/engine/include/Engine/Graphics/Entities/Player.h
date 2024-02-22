#pragma once

#include "Entity.h"

class Player : public Entity {
public:
    Player(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, F32 speed) : Entity(TexturesName::Player, position, size, velocity, speed) { }
    ~Player() = default;

    void Update(F32 deltaTime) override {
        // Reset velocity before processing input
        Velocity.x = 0.0f;
        Velocity.y = 0.0f;

        if (sInputManager->IsKeyDown(SDLK_w)) {
            Velocity.y = 1.0f; // Positive y velocity for moving up
        }
        if (sInputManager->IsKeyDown(SDLK_s)) {
            Velocity.y = -1.0f; // Negative y velocity for moving down
        }
        if (sInputManager->IsKeyDown(SDLK_a)) {
            Velocity.x = -1.0f; // Negative x velocity for moving left
        }
        if (sInputManager->IsKeyDown(SDLK_d)) {
            Velocity.x = 1.0f; // Positive x velocity for moving right
        }

        // Normalize velocity if necessary
        if (Velocity.x != 0.0f || Velocity.y != 0.0f) {
            // Normalize only if there's movement
            float length = sqrt(Velocity.x * Velocity.x + Velocity.y * Velocity.y);
            Velocity.x /= length;
            Velocity.y /= length;
        }

        // Update position
        Position.x += Velocity.x * Speed * deltaTime;
        Position.y += Velocity.y * Speed * deltaTime;
    }

    void Draw(SpriteBatch& spriteBatch) override {
        glm::vec4 destRect(Position.x, Position.y, Size.x, Size.y);
        glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

        spriteBatch.Draw(destRect, uvRect, Texture.Id, 0.0f, Color);
    }
};
