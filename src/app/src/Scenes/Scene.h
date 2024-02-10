#pragma once

#include "Engine/Graphics/SpriteBatch.h"

class Scene {
public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Initialize(U32 width, U32 height) = 0;
    virtual void Update() = 0;
    virtual void Draw(SpriteBatch& spriteBatch) = 0;
    virtual void Shutdown() = 0;
};
