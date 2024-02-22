#pragma once

#include <Common/Types.h>
#include <glm/glm.hpp>
#include "Engine/Graphics/Raw/Vertex.h"
#include "Entity.h"
#include "Engine/Graphics/Light.h"


class Projectile : public Entity{
public:
    Projectile(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, F32 speed, F32 lifeTime) : Entity(TexturesName::Ball, position, size, velocity, speed) {
        _lifeTime = lifeTime;
        _light = new Light(position, 256.0f, ColorRGBA8::Random(128));
    }
    ~Projectile() {
    }

    void Update(F32 deltaTime) override {
        Position += Velocity * Speed * deltaTime;
        _light->Position = Position;
        _lifeTime -= 1;
    }

    F32 GetLifeTime() const {
        return _lifeTime;
    }

    void Draw(SpriteBatch& spriteBatch) override {
        glm::vec4 destRect(Position.x - Size.x / 2.f, Position.y - Size.y / 2.f, Size);
        glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

        spriteBatch.Draw(destRect, uvRect, Texture.Id, 0.0f, Color);
    };

    Light* GetLight() const {
        return _light;
    }

private:
    F32 _lifeTime;
    Light* _light;
};
