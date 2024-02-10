#pragma once

#include <Common/Types.h>
#include <unordered_map>
#include "Scene.h"

class SceneManager {
public:
    static SceneManager* Instance() {
        static SceneManager instance;
        return &instance;
    };

    void AddScene(const std::string& id, Scene* scene, U32 width, U32 height) {
        _scenes[id] = scene;
        scene->Initialize(width, height);
    }

    void SetActiveScene(const std::string& id) {
        _activeScene = id;
    }

    void Update() {
        _scenes[_activeScene]->Update();
    }

    void Draw(SpriteBatch& spriteBatch) {
        _scenes[_activeScene]->Draw(spriteBatch);
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

    std::unordered_map<std::string, Scene*> _scenes;
    std::string _activeScene;
};

#define sSceneManager SceneManager::Instance()
