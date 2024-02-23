#pragma once

#include <Common/Types.h>

#include "Engine/Graphics/Raw/Shader.h"
#include "Engine/Graphics/SpriteBatch.h"
#include "Engine/Graphics/GameObjects/Entities/Entity.h"
#include "Engine/Graphics/Maps/MapLayer.h"

class MapRenderer {
public:
    ~MapRenderer() { }

    virtual void Render(SpriteBatch& spriteBatch, const std::vector<MapLayer*>& layers, const glm::mat4& projetionMatrix) {

        if (_shader == nullptr) {
            _shader = std::make_unique<Shader>();
            _shader->Init("shaders/mapShading.vert", "shaders/mapShading.frag");
            _shader->AddAttribute("a_position");
            _shader->AddAttribute("a_texCoord");
            _shader->Link();
        }

        _shader->Bind();

        //spriteBatch.Begin();

        glActiveTexture(GL_TEXTURE0);

        auto projectionLocation = _shader->GetUniformLocation("u_projectionMatrix");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &(projetionMatrix[0][0]));

        auto a = _shader->GetUniformLocation("u_tileMap");
        glUniform1i(a, 0);
        auto b = _shader->GetUniformLocation("u_lookupMap");
        glUniform1i(b, 1);

        for (auto& layer : layers) {
            layer->Draw();
        }

        //spriteBatch.End();
        //spriteBatch.Render();

        glBindTexture(GL_TEXTURE_2D, 0);

        _shader->Unbind();
    }

protected:
    std::unique_ptr<Shader> _shader;
};
