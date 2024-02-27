#pragma once

#include "Engine/Graphics/Raw/Texture.h"
#include <glm/glm.hpp>


class SpriteSheet {
public:
    void Init(Texture texture, glm::ivec2 size, glm::ivec2 cellSize) {
        _texture = texture;
        _size = size;
        _cellSize = cellSize;
    }

    glm::vec4 GetUVs(int index) const {
        int xTile = index % _size.x;
        int yTile = index / _size.x;

        glm::vec4 uvs;
        uvs.x = xTile * _cellSize.x / (F32)_texture.Width;
        uvs.y = yTile * _cellSize.y / (F32)_texture.Height;
        uvs.z = _cellSize.x / (F32)_texture.Width;
        uvs.w = _cellSize.y / (F32)_texture.Height;

        return uvs;
    }

private:
    Texture _texture;
    glm::ivec2 _size;
    glm::ivec2 _cellSize;
};
