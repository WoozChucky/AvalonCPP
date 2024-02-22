#pragma once

#include <Engine/Graphics/Raw/Texture.h>
#include <Common/Utilities/FileUtils.h>
#include <Engine/Graphics/picopng.h>
#include <GL/glew.h>
#include <map>
#include <string>

enum class TexturesName {
    Player,
    Enemy,
    Background,
    Ball
};

class AssetManager {
public:

    static AssetManager* Instance() {
        static AssetManager instance;
        return &instance;
    };

    bool Initialize() {
        return true;
    };

    void Shutdown() {
        for (auto& texture : _textures) {
            glDeleteTextures(1, &texture.second.Id);
        }
        LOG_INFO("graphics", "AssetManager shutdown");
    };

    Texture GetTexture(TexturesName name) {
        std::string filePath;
        switch (name) {
            case TexturesName::Player:
                filePath = "Assets/Textures/player.png";
                break;
            case TexturesName::Enemy:
                filePath = "Assets/Textures/cursor.png";
                break;
            case TexturesName::Background:
                filePath = "Assets/Textures/background.png";
                break;
            case TexturesName::Ball:
                filePath = "Assets/Textures/icon.png";
                break;
        }

        if (_textures.find(name) == _textures.end()) {
            _textures[name] = LoadTexture(filePath);
        }

        return _textures[name];
    }

private:



    std::map<TexturesName, Texture> _textures;

    Texture LoadTexture(const std::string& filePath) {

        Texture texture = {};

        std::vector<U8> in;
        std::vector<U8> out;


        if (!File::ReadBinaryContent(filePath, in)) {
            throw std::runtime_error("Failed to read file: " + filePath);
        }

        std::vector<U8> image;
        unsigned long width, height;

        int error = decodePNG(out, width, height, in.data(), in.size());

        if (error != 0) {
            throw std::runtime_error("Failed to decode PNG: " + filePath);
        }

        texture.Width = width;
        texture.Height = height;

        glGenTextures(1, &texture.Id);
        glBindTexture(GL_TEXTURE_2D, texture.Id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, out.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        return texture;
    };

    void UnloadTexture(TexturesName name) {
        if (_textures.find(name) == _textures.end()) {
            LOG_WARN("graphics", "Texture not found: {}", std::to_string(static_cast<int>(name)));
            return;
        }
        Texture texture = _textures[name];
        glDeleteTextures(1, &texture.Id);

        _textures.erase(name);
    };

};

#define sAssetManager AssetManager::Instance()
