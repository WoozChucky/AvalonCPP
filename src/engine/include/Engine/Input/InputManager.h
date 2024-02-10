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

private:
    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    std::unordered_map<U32, bool> _keys;
};

#define sInputManager InputManager::Instance()
