#pragma once

#include "SpriteBatch.h"

class IDrawable {
public:
    virtual void Draw(SpriteBatch& spriteBatch) = 0;
};
