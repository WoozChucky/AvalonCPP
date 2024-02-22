#pragma once

#include <SDL_keycode.h>
#include <SDL_mouse.h>
#include <Box2D/Box2D.h>

#include "Scene.h"
#include "Engine/Graphics/Camera2D.h"
#include "Engine/Graphics/SpriteBatch.h"
#include "Engine/Graphics/Renderers/ProjectileRenderer.h"
#include "Engine/Graphics/Renderers/EntityRenderer.h"
#include "Engine/Graphics/Entities/Player.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Graphics/Renderers/DebugRenderer.h"
#include "Engine/Graphics/Entities/Enemy.h"
#include "Engine/Graphics/Renderers/LightRenderer.h"
#include "Engine/Graphics/Light.h"

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

        _playerLight = new Light(glm::vec2(0.0f, 0.0f), 256.0f * 2, ColorRGBA8(128, 128, 128, 128));
        _mouseLight = new Light(glm::vec2(0.0f, 0.0f), 128.0f * 2, ColorRGBA8(0, 153, 153, 150));

        _lights.emplace_back(_playerLight);
        _lights.emplace_back(_mouseLight);

        _spriteBatch.Initialize();

        _debugRenderer.Init();
    };

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

    void Update(F32 deltaTime) override {

        static S32 mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        _mouseLight->Position = _camera.ConvertScreenToWorld(glm::vec2(mouseX, mouseY));

        if (sInputManager->IsKeyPressed(SDLK_F5)) {
           _debugRender = !_debugRender;
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

            glm::vec2 direction = glm::normalize(mouseCoords - _player->GetPosition());

            _projectiles.emplace_back(new Projectile(_player->GetPosition(), glm::vec2(64, 64), direction, 100.f, 1000));
        }

        _playerLight->Position = _player->GetPosition() + glm::vec2(_player->GetSize().x / 2.f);
        _camera.SetPosition(_player->GetPosition());
        _camera.Update();

        for (auto entity : _entities) {
            entity->Update(deltaTime);
        }

        for(auto i = 0; i < _projectiles.size();) {
            _projectiles[i]->Update(deltaTime);
            if (_projectiles[i]->GetLifeTime() == 0) {
                delete _projectiles[i]; // Delete the object
                _projectiles[i] = _projectiles.back();
                _projectiles.pop_back();
            } else {
                ++i;
            }
        }
    };

    void Draw() override {
        _entityRenderer.Render(_spriteBatch, _entities, _camera.GetCameraMatrix());
        //_projectileRenderer.Render(_spriteBatch, _projectiles, _camera.GetCameraMatrix());
        _lightRenderer.Render(_spriteBatch, _lights, _camera.GetCameraMatrix());
        _lightRenderer.Render(_spriteBatch, getLightsFromProjectiles(_projectiles), _camera.GetCameraMatrix());

        if (_debugRender) {
            for (auto& projectile : _projectiles) {
                glm::vec4 destRect(projectile->GetPosition().x, projectile->GetPosition().y, projectile->GetSize());
                _debugRenderer.DrawCircle(destRect, ColorRGBA8(255, 255, 255, 255), projectile->GetSize().x / 2.f);
            }

            for (auto& entity : _entities) {
                glm::vec4 destRect(entity->GetPosition().x, entity->GetPosition().y, entity->GetSize());
                _debugRenderer.DrawBox(destRect, ColorRGBA8(255, 255, 255, 255), 0.0f);
            }

            _debugRenderer.End();
            _debugRenderer.Render(_camera.GetCameraMatrix(), 1.0f);
        }
    };

    void Shutdown() override {

        for (auto& entity : _entities) {
            delete entity;
        }
        _entities.clear();
        for (auto& projectile : _projectiles) {
            delete projectile;
        }
        _projectiles.clear();
        for (auto& light : _lights) {
            delete light;
        }
        _lights.clear();

        _debugRenderer.Dispose();
        LOG_INFO("game", "Shutting down TestingScene");
    };

private:
    Camera2D _camera;
    SpriteBatch _spriteBatch;

    DebugRenderer _debugRenderer;

    ProjectileRenderer _projectileRenderer;
    std::vector<Projectile*> _projectiles;

    EntityRenderer _entityRenderer;
    std::vector<Entity*> _entities;

    LightRenderer _lightRenderer;
    Light* _playerLight;
    Light* _mouseLight;
    std::vector<Light*> _lights;

    Player* _player{};

    bool _debugRender = false;

    std::vector<Light*> getLightsFromProjectiles(std::vector<Projectile*>& projectiles) {
        std::vector<Light*> lights(projectiles.size());

        // Use std::transform to extract light pointers from projectiles
        std::transform(projectiles.begin(), projectiles.end(), lights.begin(),
                       [](const Projectile* projectilePtr) { return projectilePtr->GetLight(); });

        return lights;
    }

};
