#pragma once

#include <Common/Types.h>
#include "Engine/Graphics/Raw/Vertex.h"
#include "Engine/Graphics/Raw/Texture.h"
#include "Engine/Graphics/IDrawable.h"
#include "Engine/Graphics/AssetManager.h"
#include "Engine/Graphics/GameObjects/GameObject.h"
#include <glm/glm.hpp>

class Torch : public GameObject {

public:
    explicit Torch(glm::vec2 position, F32 size, ColorRGBA8 color)
        : GameObject(TexturesName::Torch, position, glm::vec2(size, size)) {
    }
    ~Torch() = default;

    void Update(F32 deltaTime) override {
    }

};
