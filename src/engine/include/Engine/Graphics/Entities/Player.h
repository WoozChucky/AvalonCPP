#pragma once

#include "Entity.h"
#include "Engine/Graphics/SpriteSheet.h"

class Player : public Entity {
public:
    Player(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, F32 speed) : Entity(TexturesName::Player, position, size, velocity, speed) {
        _spriteSheet.Init(Texture, glm::ivec2(3, 4), glm::ivec2(32, 32));
    }
    ~Player() {}

    void Update(F32 deltaTime) override {
        // Reset velocity before processing input
        Velocity.x = 0.0f;
        Velocity.y = 0.0f;

        bool isMoving = false;

        if (sInputManager->IsKeyDown(SDLK_w)) {
            Velocity.y = 1.0f; // Positive y velocity for moving up
            _lastMoveDirection = glm::vec2(0.0f, 1.0f);
            isMoving = true;
        }
        if (sInputManager->IsKeyDown(SDLK_s)) {
            Velocity.y = -1.0f; // Negative y velocity for moving down
            _lastMoveDirection = glm::vec2(0.0f, -1.0f);
            isMoving = true;
        }
        if (sInputManager->IsKeyDown(SDLK_a)) {
            Velocity.x = -1.0f; // Negative x velocity for moving left
            _lastMoveDirection = glm::vec2(-1.0f, 0.0f);
            isMoving = true;
        }
        if (sInputManager->IsKeyDown(SDLK_d)) {
            Velocity.x = 1.0f; // Positive x velocity for moving right
            _lastMoveDirection = glm::vec2(1.0f, 0.0f);
            isMoving = true;
        }

        // Normalize velocity if necessary
        if (isMoving && (Velocity.x != 0.0f || Velocity.y != 0.0f)) {
            // Normalize only if there's movement
            float length = sqrt(Velocity.x * Velocity.x + Velocity.y * Velocity.y);
            Velocity.x /= length;
            Velocity.y /= length;

            // Update animation frame based on elapsed time
            _timeSinceLastFrame += deltaTime;
            if (_timeSinceLastFrame >= _frameTime) {
                _timeSinceLastFrame -= _frameTime; // Reset timer

                // Advance to the next frame
                _currentFrame++;
                if (_currentFrame >= 3) {
                    _currentFrame = 0; // Reset to the first frame if at the end of the animation cycle
                }
            }
        } else {
            // If the player is not moving, use the last movement direction to determine the animation index
            _currentFrame = GetAnimationIndexFromDirection(_lastMoveDirection);
        }

        // Update position
        Position.x += Velocity.x * Speed * deltaTime;
        Position.y += Velocity.y * Speed * deltaTime;
    }

    void Draw(SpriteBatch& spriteBatch) override {
        glm::vec4 destRect(Position.x, Position.y, Size.x, Size.y);

        int animationIndex = GetAnimationIndex();
        glm::vec4 uvRect = _spriteSheet.GetUVs(animationIndex);

        spriteBatch.Draw(destRect, uvRect, Texture.Id, 0.0f, Color);
    }

private:
    SpriteSheet _spriteSheet;

    U32 _currentFrame = 0;
    F32 _frameTime = 0.20f;
    F32 _timeSinceLastFrame = 0.0f;
    glm::vec2 _lastMoveDirection;

    // UVs (0 to 2) are facing down,
    // UVs (3 to 5) are facing right,
    // UVs (6 to 8) are facing left,
    // UVs (9 to 11) are facing up
    int GetAnimationIndex() const {
        // Determine animation index based on player input
        if (Velocity.x > 0.0f) {
            return 3 + (_currentFrame % 3); // Right-facing animation (frames 3, 4, 5)
        } else if (Velocity.x < 0.0f) {
            return 6 + (_currentFrame % 3); // Left-facing animation (frames 6, 7, 8)
        } else if (Velocity.y > 0.0f) {
            return _currentFrame % 3; // Down-facing animation (frames 0, 1, 2)
        } else if (Velocity.y < 0.0f) {
            return 9 + (_currentFrame % 3); // Up-facing animation (frames 9, 10, 11)
        } else {
            // If the player is not moving, use the last movement direction to determine the animation index
            return GetAnimationIndexFromDirection(_lastMoveDirection);
        }
    }

    int GetAnimationIndexFromDirection(glm::vec2 direction) const {
        // Determine animation index based on player direction
        if (direction.x > 0.0f) {
            return 3 + (_currentFrame % 3); // Right-facing animation (frames 3, 4, 5)
        } else if (direction.x < 0.0f) {
            return 6 + (_currentFrame % 3); // Left-facing animation (frames 6, 7, 8)
        } else if (direction.y > 0.0f) {
            return _currentFrame % 3; // Down-facing animation (frames 0, 1, 2)
        } else if (direction.y < 0.0f) {
            return 9 + (_currentFrame % 3); // Up-facing animation (frames 9, 10, 11)
        } else {
            return 0; // Default animation (standing still, frames 0, 1, 2)
        }
    }
};
