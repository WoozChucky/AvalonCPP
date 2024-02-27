#pragma once

#include <Common/Types.h>
#include <glm/glm.hpp>
#include <unordered_map>

class InputManager {
public:
    static InputManager* Instance() {
        static InputManager instance;
        return &instance;
    };

    void Update() {
        _previousKeys = _keys;
    }

    void PressKey(U32 key) {
        _keys[key] = true;
    }
    void ReleaseKey(U32 key) {
        _keys[key] = false;
    }

    bool IsKeyPressed(U32 key) {
        return IsKeyDown(key) && !_previousKeys[key];
    }

    bool IsKeyReleased(U32 key) {
        return !IsKeyDown(key) && _previousKeys[key];
    }

    bool IsKeyDown(U32 key) {
        auto it = _keys.find(key);
        if (it != _keys.end()) {
            return it->second;
        }
        return false;
    }

    void SetMouseCoords(F32 x, F32 y) {
        _mouseCoords.x = x;
        _mouseCoords.y = y;
    }

    void SetMouseWheel(F32 x, F32 y) {
        _mouseWheel.x = x;
        _mouseWheel.y = y;
    }

    glm::vec2 GetMouseWheel() const {
        return _mouseWheel;
    }

    glm::vec2 GetMouseCoords() const {
        return _mouseCoords;
    }

private:
    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    std::unordered_map<U32, bool> _keys;
    std::unordered_map<U32, bool> _previousKeys;
    glm::vec2 _mouseCoords = glm::vec2(0.0f);
    glm::vec2 _mouseWheel = glm::vec2(0.0f);
};

#define sInputManager InputManager::Instance()
