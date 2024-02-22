#pragma once

#include <Common/Types.h>
#include <glm/glm.hpp>
#include "Engine/Graphics/Raw/Texture.h"
#include "Engine/Graphics/Raw/Vertex.h"
#include "Engine/Graphics/AssetManager.h"
#include "Engine/Graphics/SpriteBatch.h"

class Entity {
public:
    Entity(TexturesName textureName, glm::vec2 position, glm::vec2 size, glm::vec2 velocity, F32 speed) {
        Position = position;
        Size = size;
        Velocity = velocity;
        Speed = speed;
        Texture = AssetManager::Instance()->GetTexture(textureName);
    }

    virtual void SetPosition(glm::vec2 position) {
        Position = position;
    }

    virtual glm::vec2 GetPosition() const {
        return Position;
    }

    virtual void SetVelocity(glm::vec2 velocity) {
        Velocity = velocity;
    }

    virtual glm::vec2 GetVelocity() const {
        return Velocity;
    }

    virtual void SetSpeed(F32 speed) {
        Speed = speed;
    }

    virtual F32 GetSpeed() const {
        return Speed;
    }

    virtual void SetSize(glm::vec2 size) {
        Size = size;
    }

    virtual glm::vec2 GetSize() const {
        return Size;
    }

    virtual void Update(F32 deltaTime) {
        Position += Velocity * Speed * deltaTime;
    };

    virtual void Draw(SpriteBatch& spriteBatch) {
        glm::vec4 destRect(Position.x, Position.y, Size.x, Size.y);
        glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

        spriteBatch.Draw(destRect, uvRect, Texture.Id, 0.0f, Color);
    };

protected:
    Texture Texture;
    F32 Speed;
    glm::vec2 Position;
    glm::vec2 Velocity;
    glm::vec2 Size;
    ColorRGBA8 Color = { 255, 255, 255, 255 };
};
