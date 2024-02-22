#pragma once

#include <Common/Types.h>
#include <glm/glm.hpp>
#include "Engine/Graphics/Raw/Vertex.h"
#include "Entity.h"


class Projectile : public Entity{
public:
    Projectile(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, F32 speed, F32 lifeTime) : Entity(TexturesName::Ball, position, size, velocity, speed) {
        _lifeTime = lifeTime;
    }
    ~Projectile() {}

    void Update(F32 deltaTime) override {
        Position += Velocity * Speed * deltaTime;
        _lifeTime -= 1;
    }

    F32 GetLifeTime() const {
        return _lifeTime;
    }

private:
    F32 _lifeTime;
};
