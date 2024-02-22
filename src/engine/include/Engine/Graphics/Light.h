#pragma once

#include <Common/Types.h>
#include "Engine/Graphics/Raw/Vertex.h"
#include "SpriteBatch.h"
#include <glm/glm.hpp>

class Light {

public:
    explicit Light(glm::vec2 position, F32 size, ColorRGBA8 color) {
        Position = position;
        Size = size;
        Color = color;
    }

    void Draw(SpriteBatch& spriteBatch) {
        glm::vec4 destRect(Position.x - Size / 2.f, Position.y - Size / 2.f, Size, Size);

        glm::vec4 uvRect(-1, -1, 2, 2);

        spriteBatch.Draw(destRect, uvRect, 0, 0.0f, Color, 0.0f);
    }

    ColorRGBA8 Color;
    glm::vec2 Position;
    F32 Size;
};
