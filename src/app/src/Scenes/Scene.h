#pragma once

#include <SDL_events.h>
#include "Common/Types.h"

class IScene {
public:
    IScene() = default;
    virtual ~IScene() = default;

    virtual void Initialize(U32 width, U32 height) = 0;
    virtual void onSDLEvent(SDL_Event& event) = 0;
    virtual void Update(F32 deltaTime) = 0;
    virtual void Draw(F32 deltaTime) = 0;
    virtual void Shutdown() = 0;
};
