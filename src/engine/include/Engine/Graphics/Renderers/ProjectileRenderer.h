#pragma once

#include "Common/Types.h"

#include "Engine/Graphics/Raw/Shader.h"
#include "Engine/Graphics/SpriteBatch.h"
#include "Engine/Graphics/GameObjects/Entities/Projectile.h"

class ProjectileRenderer {
public:
    ~ProjectileRenderer() { }

    virtual void Render(SpriteBatch& spriteBatch, const std::vector<Projectile*>& projectiles, const glm::mat4& projetionMatrix) {

        if (_shader == nullptr) {
            _shader = std::make_unique<Shader>();
            _shader->Init("shaders/colorShading.vert", "shaders/colorShading.frag");
            _shader->AddAttribute("position");
            _shader->AddAttribute("color");
            _shader->AddAttribute("textCoord");
            _shader->Link();
        }

        _shader->Bind();

        spriteBatch.Begin();

        glActiveTexture(GL_TEXTURE0);
        auto textureLocation = _shader->GetUniformLocation("spriteTexture");
        glUniform1i(textureLocation, 0);

        auto projectionLocation = _shader->GetUniformLocation("projection");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &(projetionMatrix[0][0]));

        for (auto& projectile : projectiles) {
            projectile->Draw(spriteBatch);
        }

        spriteBatch.End();
        spriteBatch.Render();

        glBindTexture(GL_TEXTURE_2D, 0);

        _shader->Unbind();
    }

    private:
        std::unique_ptr<Shader> _shader;
};
