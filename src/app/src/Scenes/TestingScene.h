#pragma once

#include <SDL_keycode.h>
#include <SDL_mouse.h>
#include "Scene.h"
#include "Engine/Graphics/Camera2D.h"
#include "Engine/Graphics/SpriteBatch.h"
#include "Engine/Graphics/ProjectileRenderer.h"
#include "Engine/Graphics/EntityRenderer.h"
#include "Engine/Graphics/Player.h"
#include "Engine/Input/InputManager.h"

class TestingScene : public IScene {

public:
    TestingScene() = default;
    ~TestingScene() override = default;

    void Initialize(U32 width, U32 height) override {
        _camera.Init(width, height);

        _player = new Player(glm::vec2(0.0f, 0.0f), glm::vec2(128.0f, 128.0f), glm::vec2(0.0f, 0.0f), 1.f);

        _entities.emplace_back(*_player);

        _spriteBatch.Initialize();

    };

    void onSDLEvent(SDL_Event& event) override {
        switch (event.type) {
            case SDL_MOUSEWHEEL:
                if (sInputManager->GetMouseWheel().y > 0) {
                    _camera.SetScale(_camera.GetScale() + 0.1f);
                } else if (sInputManager->GetMouseWheel().y < 0) {
                    _camera.SetScale(_camera.GetScale() - 0.1f);
                }
                break;
        }
    };

    void Update(F32 deltaTime) override {

        if (sInputManager->IsKeyDown(SDLK_w)) {
            _camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, 10.0f));
        }
        if (sInputManager->IsKeyDown(SDLK_s)) {
            _camera.SetPosition(_camera.GetPosition() + glm::vec2(0.0f, -10.0f));
        }
        if (sInputManager->IsKeyDown(SDLK_a)) {
            _camera.SetPosition(_camera.GetPosition() + glm::vec2(-10.0f, 0.0f));
        }
        if (sInputManager->IsKeyDown(SDLK_d)) {
            _camera.SetPosition(_camera.GetPosition() + glm::vec2(10.0f, 0.0f));
        }
        if (sInputManager->IsKeyDown(SDLK_q)) {
            _camera.SetScale(_camera.GetScale() + 0.1f);
        }
        if (sInputManager->IsKeyDown(SDLK_e)) {
            _camera.SetScale(_camera.GetScale() - 0.1f);
        }

        if (sInputManager->IsKeyDown(SDL_BUTTON_LEFT)) {
            glm::vec2 mouseCoords = sInputManager->GetMouseCoords();
            mouseCoords = _camera.ConvertScreenToWorld(mouseCoords);
            // LOG_INFO("game", "Mouse Coords: ({}, {})", mouseCoords.x, mouseCoords.y);
            glm::vec2 playerPosition(0.0f);
            glm::vec2 direction = glm::normalize(mouseCoords - playerPosition);

            _projectiles.emplace_back(playerPosition, direction, 1.f, 1000);
        }

        _camera.Update();

        for(auto i = 0; i < _projectiles.size();) {
            _projectiles[i].Update(1);
            if (_projectiles[i].GetLifeTime() == 0) {
                _projectiles[i] = _projectiles.back();
                _projectiles.pop_back();
            } else {
                ++i;
            }
        }
    };

    void Draw() override {
        _entityRenderer.Render(_spriteBatch, _entities, _camera.GetCameraMatrix());
        _projectileRenderer.Render(_spriteBatch, _projectiles, _camera.GetCameraMatrix());
    };

    void Shutdown() override {
        LOG_INFO("game", "Shutting down TestingScene");
    };

private:
    Camera2D _camera;
    SpriteBatch _spriteBatch;

    ProjectileRenderer _projectileRenderer;
    std::vector<Projectile> _projectiles;

    EntityRenderer _entityRenderer;
    std::vector<Entity> _entities;
    Player* _player{};

};
