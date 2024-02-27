#pragma once

#include "Engine/Graphics/SpriteBatch.h"
#include "Engine/Graphics/Raw/Shader.h"
#include "Engine/Graphics/GameObjects/Lights/TorchLight.h"

class TorchRenderer {
public:
    virtual void Render(SpriteBatch& spriteBatch, const std::vector<TorchLight*>& torchs, const glm::mat4& projetionMatrix, F32 deltaTime) {
        if (_shader == nullptr) {
            _shader = std::make_unique<Shader>();
            _shader->Init("shaders/lightShading.vert", "shaders/torchShading.frag");
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

        static F32 time = 0.0f;
        time += deltaTime;

        auto timeLocation = _shader->GetUniformLocation("time");
        glUniform1f(timeLocation, time);

        // Draw all the lights
        for (auto& torch : torchs) {
            torch->Draw(spriteBatch);
        }

        spriteBatch.End();
        spriteBatch.Render();

        _shader->Unbind();

        // Reset to default blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);
    }

protected:
    std::unique_ptr<Shader> _shader;
};
