#pragma once

#include <Common/Types.h>
#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, F32 speed) : Entity(TexturesName::Enemy, position, size, velocity, speed) {
    }
    ~Enemy() = default;

};
