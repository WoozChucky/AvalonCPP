#pragma once

#include <SDL_keycode.h>
#include <SDL_mouse.h>
#include "Scene.h"
#include "Engine/Graphics/Camera2D.h"
#include "Engine/Graphics/SpriteBatch.h"
#include "Engine/Graphics/Renderers/ProjectileRenderer.h"
#include "Engine/Graphics/Renderers/EntityRenderer.h"
#include "Engine/Graphics/Entities/Player.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Graphics/Renderers/DebugRenderer.h"
#include "Engine/Graphics/Entities/Enemy.h"

class TestingScene : public IScene {

public:
    TestingScene() = default;
    ~TestingScene() override = default;

    void Initialize(U32 width, U32 height) override {
        _camera.Init(width, height);

        _player = new Player(glm::vec2(0.0f, 0.0f), glm::vec2(64.0f, 64.0f), glm::vec2(0.0f, 0.0f), 100.f);

        _entities.emplace_back(_player);
        _entities.emplace_back(new Enemy(glm::vec2(100.0f, 0.0f), glm::vec2(128.0f, 128.0f), glm::vec2(0.0f, 0.0f), 100.f));
        _entities.emplace_back(new Enemy(glm::vec2(-600.0f, 0.0f), glm::vec2(128.0f, 128.0f), glm::vec2(0.0f, 0.0f), 100.f));
        _entities.emplace_back(new Enemy(glm::vec2(100.0f, 200.0f), glm::vec2(128.0f, 128.0f), glm::vec2(0.0f, 0.0f), 100.f));

        _spriteBatch.Initialize();

        _debugRenderer.Init();
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

        /*
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
        */
        if (sInputManager->IsKeyDown(SDLK_q)) {
            _camera.SetScale(_camera.GetScale() + 0.1f);
        }
        if (sInputManager->IsKeyDown(SDLK_e)) {
            _camera.SetScale(_camera.GetScale() - 0.1f);
        }

        if (sInputManager->IsKeyDown(SDL_BUTTON_LEFT)) {
            glm::vec2 mouseCoords = sInputManager->GetMouseCoords();
            mouseCoords = _camera.ConvertScreenToWorld(mouseCoords);

            glm::vec2 direction = glm::normalize(mouseCoords - _player->GetPosition());

            _projectiles.emplace_back(_player->GetPosition(), glm::vec2(64, 64), direction, 100.f, 1000);
        }

        _camera.SetPosition(_player->GetPosition());
        _camera.Update();

        for (auto entity : _entities) {
            entity->Update(deltaTime);
        }

        for(auto i = 0; i < _projectiles.size();) {
            _projectiles[i].Update(deltaTime);
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


        for (auto& projectile : _projectiles) {
            glm::vec4 destRect(projectile.GetPosition().x, projectile.GetPosition().y, projectile.GetSize());
            _debugRenderer.DrawCircle(destRect, ColorRGBA8(255, 255, 255, 255), projectile.GetSize().x / 2.f);
        }

        for (auto& entity : _entities) {
            glm::vec4 destRect(entity->GetPosition().x, entity->GetPosition().y, entity->GetSize());
            _debugRenderer.DrawBox(destRect, ColorRGBA8(255, 255, 255, 255), 0.0f);
        }

        _debugRenderer.End();
        _debugRenderer.Render(_camera.GetCameraMatrix(), 1.0f);
    };

    void Shutdown() override {
        _debugRenderer.Dispose();
        LOG_INFO("game", "Shutting down TestingScene");
    };

private:
    Camera2D _camera;
    SpriteBatch _spriteBatch;

    DebugRenderer _debugRenderer;

    ProjectileRenderer _projectileRenderer;
    std::vector<Projectile> _projectiles;

    EntityRenderer _entityRenderer;
    std::vector<Entity*> _entities;

    Player* _player{};

};
