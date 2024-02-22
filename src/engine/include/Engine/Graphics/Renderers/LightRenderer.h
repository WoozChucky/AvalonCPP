#pragma once

#include <Common/Types.h>
#include "Engine/Graphics/SpriteBatch.h"
#include "Engine/Graphics/Raw/Shader.h"
#include "Engine/Graphics/Light.h"

class LightRenderer {
public:
    virtual void Render(SpriteBatch& spriteBatch, const std::vector<Light*>& lights, const glm::mat4& projetionMatrix) {
        if (_shader == nullptr) {
            _shader = std::make_unique<Shader>();
            _shader->Init("shaders/lightShading.vert", "shaders/lightShading.frag");
            _shader->AddAttribute("position");
            _shader->AddAttribute("color");
            _shader->AddAttribute("textCoord");
            _shader->Link();
        }

        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        _shader->Bind();

        spriteBatch.Begin();

        auto projectionLocation = _shader->GetUniformLocation("projection");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &(projetionMatrix[0][0]));

        // Draw all the lights
        for (auto& light : lights) {
            light->Draw(spriteBatch);
        }

        spriteBatch.End();
        spriteBatch.Render();

        _shader->Unbind();

        // Reset to default blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

protected:
    std::unique_ptr<Shader> _shader;
};
