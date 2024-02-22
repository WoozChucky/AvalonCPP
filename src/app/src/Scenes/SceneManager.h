#pragma once

#include "Scene.h"
#include <unordered_map>

class SceneManager {
public:
    static SceneManager* Instance() {
        static SceneManager instance;
        return &instance;
    };

    void Initialize() {
        _scenes.clear();
        _activeScene.clear();
    }

    void AddScene(const std::string& id, IScene* scene, U32 width, U32 height) {
        _scenes[id] = scene;
        scene->Initialize(width, height);
    }

    void SetActiveScene(const std::string& id) {
        _activeScene = id;
    }

    void onSDLEvent(SDL_Event& event) {
        _scenes[_activeScene]->onSDLEvent(event);
    }

    void Update(F32 deltaTime) {
        _scenes[_activeScene]->Update(deltaTime);
    }

    void Draw() {
        _scenes[_activeScene]->Draw();
    }

    void Shutdown() {
        for (auto& scene : _scenes) {
            scene.second->Shutdown();
            scene.second = nullptr;
        }
    }

private:
    SceneManager() = default;
    ~SceneManager() = default;
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    std::unordered_map<std::string, IScene*> _scenes;
    std::string _activeScene;
};

#define sSceneManager SceneManager::Instance()
