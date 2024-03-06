#pragma once

#include <tmxlite/Map.hpp>

#include "Scene.h"
#include "Engine/Graphics/Camera2D.h"
#include "Engine/Graphics/SpriteBatch.h"
#include "Engine/Graphics/GameObjects/Entities/Player.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Graphics/GameObjects/Entities/Enemy.h"
#include "Engine/Graphics/GameObjects/Lights/Light.h"
#include "Engine/Graphics/Maps/MapLayer.h"
#include "Engine/Graphics/GameObjects/Lights/TorchLight.h"
#include "Engine/Graphics/GameObjects/Entities/Torch.h"

#if 0
        // When doing shadow stuff
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        // After doing shadow stuff
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);
#endif

class TestingScene : public IScene {

public:
    TestingScene() = default;
    ~TestingScene() override = default;

    void Initialize(U32 width, U32 height) override {
        _camera.Init(width, height);

        _player = new Player(glm::vec2(0.0f, 0.0f), glm::vec2(64.0f, 64.0f), glm::vec2(0.0f, 0.0f), 100.f);

        _gameObjects.emplace_back(_player);
        _gameObjects.emplace_back(new Enemy(glm::vec2(100.0f, 0.0f), glm::vec2(128.0f, 128.0f), glm::vec2(0.0f, 0.0f), 100.f));
        _gameObjects.emplace_back(new Enemy(glm::vec2(-600.0f, 0.0f), glm::vec2(128.0f, 128.0f), glm::vec2(0.0f, 0.0f), 100.f));
        _gameObjects.emplace_back(new Enemy(glm::vec2(100.0f, 200.0f), glm::vec2(128.0f, 128.0f), glm::vec2(0.0f, 0.0f), 100.f));
        _gameObjects.emplace_back(new Torch(glm::vec2(-533.0f, 450.0f), 64, ColorRGBA8::White()));

        _playerLight = new Light(glm::vec2(0.0f, 0.0f), 256.0f * 2, ColorRGBA8(128, 128, 128, 128));
        _mouseLight = new Light(glm::vec2(0.0f, 0.0f), 128.0f * 2, ColorRGBA8(0, 153, 153, 150));

        _lights.emplace_back(_playerLight);
        _lights.emplace_back(_mouseLight);

        _torchLights.emplace_back(new TorchLight(glm::vec2(-500.0f, 500.0f), 128, ColorRGBA8::White()));

        _spriteBatch.Initialize();
    };

    /*
    void onSDLEvent(SDL_Event& event) override {
        switch (event.type) {
            case SDL_MOUSEMOTION:
                break;
            case SDL_MOUSEWHEEL:
                if (sInputManager->GetMouseWheel().y > 0) {
                    _camera.SetScale(_camera.GetScale() + 0.1f);
                } else if (sInputManager->GetMouseWheel().y < 0) {
                    _camera.SetScale(_camera.GetScale() - 0.1f);
                }
                break;
        }
    };
     */

    void Update(F32 deltaTime) override {

    };

    void Draw(F32 deltaTime) override {


    };

    void Shutdown() override {

        for (auto& gameObject : _gameObjects) {
            delete gameObject;
        }
        _gameObjects.clear();
        for (auto& light : _lights) {
            delete light;
        }
        _lights.clear();
        for (auto& torch : _torchLights) {
            delete torch;
        }
        _torchLights.clear();

        LOG_INFO("game", "Shutting down TestingScene");
    };

private:
    Camera2D _camera;
    SpriteBatch _spriteBatch;



    std::vector<GameObject*> _gameObjects;

    std::vector<TorchLight*> _torchLights;

    Light* _playerLight;
    Light* _mouseLight;
    std::vector<Light*> _lights;

    Player* _player{};

    bool _debugRender = false;

};
