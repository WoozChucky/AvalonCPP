#pragma once

#include <Common/Types.h>
#include <unordered_map>

class InputManager {
public:
    static InputManager* Instance() {
        static InputManager instance;
        return &instance;
    };

    void PressKey(U32 key) {
        _keys[key] = true;
    }
    void ReleaseKey(U32 key) {
        _keys[key] = false;
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

    glm::vec2 GetMouseCoords() const {
        return _mouseCoords;
    }

private:
    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    std::unordered_map<U32, bool> _keys;
    glm::vec2 _mouseCoords = glm::vec2(0.0f);
};

#define sInputManager InputManager::Instance()
