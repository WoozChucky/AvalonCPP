#pragma once

#include <Common/Types.h>
#include <glm/glm.hpp>
#include "Engine/Graphics/Raw/Vertex.h"
#include "SpriteBatch.h"
#include "AssetManager.h"

class Projectile {
public:
    Projectile(glm::vec2 position, glm::vec2 velocity, F32 speed, F32 lifeTime) {
        _position = position;
        _velocity = velocity;
        _speed = speed;
        _lifeTime = lifeTime;
        _texture = AssetManager::Instance()->GetTexture(TexturesName::Player);
    }
    ~Projectile() = default;

    void Update(F32 deltaTime) {
        _position += _velocity * _speed;
        _lifeTime -= 1;
    }

    glm::vec2 GetPosition() const {
        return _position;
    }

    F32 GetLifeTime() const {
        return _lifeTime;
    }

    void Draw(SpriteBatch& spriteBatch) {
        Color color{};
        color.r = 255;
        color.g = 255;
        color.b = 255;
        color.a = 255;
        glm::vec4 destRect(_position.x, _position.y, 30, 30);
        glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

        spriteBatch.Draw(destRect, uvRect, _texture.Id, 0.0f, color);
    }

private:
    Texture _texture;
    glm::vec2 _position;
    glm::vec2 _velocity;
    F32 _speed;
    F32 _lifeTime;
};
