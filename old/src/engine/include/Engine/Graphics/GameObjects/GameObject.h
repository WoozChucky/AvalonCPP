#pragma once

#include "Engine/Graphics/Raw/Texture.h"
#include "Engine/Graphics/Raw/Vertex.h"
#include "Engine/Graphics/IDrawable.h"
#include "Engine/Graphics/AssetManager.h"
#include <glm/glm.hpp>

class GameObject : public IDrawable {
public:
    GameObject(TexturesName textureName, glm::vec2 position, glm::vec2 size) {
        Position = position;
        Size = size;
        Texture = sAssetManager->GetTexture(textureName);
    }

    virtual void Update(F32 deltaTime) = 0;

    virtual void Draw(SpriteBatch& spriteBatch) override {
        glm::vec4 destRect(Position.x, Position.y, Size.x, Size.y);
        glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

        spriteBatch.Draw(destRect, uvRect, Texture.Id, 0.0f, Color);
    };

    virtual void SetPosition(glm::vec2 position) {
        Position = position;
    }

    virtual glm::vec2 GetPosition() const {
        return Position;
    }

    virtual void SetSize(glm::vec2 size) {
        Size = size;
    }

    virtual glm::vec2 GetSize() const {
        return Size;
    }

protected:
    Texture Texture;
    glm::vec2 Position;
    glm::vec2 Size;
    ColorRGBA8 Color = ColorRGBA8::White();
};
