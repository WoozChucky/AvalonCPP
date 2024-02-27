#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include <Engine/Graphics/Raw/Texture.h>
#include <Engine/Graphics/stb_image.h>
#include <GL/glew.h>
#include <map>
#include <string>

enum class TexturesName {
    Player,
    Enemy,
    Background,
    Ball,
    Map,
    Torch
};

class AssetManager {
public:

    static AssetManager* Instance() {
        static AssetManager instance;
        return &instance;
    };

    bool Initialize() {
        stbi_set_flip_vertically_on_load(true);
        return true;
    };

    void Shutdown() {
        for (auto& texture : _textures) {
            glDeleteTextures(1, &texture.second.Id);
        }
        LOG_INFO("graphics", "AssetManager shutdown");
    };

    Texture GetTexture(TexturesName name, bool isAtlas = false) {
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
            case TexturesName::Map:
                filePath = "Assets/Textures/map.png";
                break;
            case TexturesName::Torch:
                filePath = "Assets/Textures/torch.png";
                break;
        }

        if (_textures.find(name) == _textures.end()) {
            _textures[name] = isAtlas ? LoadTextureAtlas(filePath) : LoadTexture(filePath);
        }

        return _textures[name];
    }

private:



    std::map<TexturesName, Texture> _textures;

    Texture LoadTexture(const std::string& filePath) {

        Texture texture = {};

        int width, height, channels;

        auto pixels = stbi_load(filePath.c_str(), &width, &height, &channels, 4);
        if (!pixels) {
            throw std::runtime_error("Failed to load image: " + filePath);
        }

        texture.Width = width;
        texture.Height = height;

        glGenTextures(1, &texture.Id);
        glBindTexture(GL_TEXTURE_2D, texture.Id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(pixels);

        return texture;
    };

    Texture LoadTextureAtlas(const std::string& filePath) {
        Texture texture = {};

        int width, height, channels;

        auto pixels = stbi_load(filePath.c_str(), &width, &height, &channels, 4);
        if (!pixels) {
            throw std::runtime_error("Failed to load image: " + filePath);
        }

        texture.Width = width;
        texture.Height = height;

        glGenTextures(1, &texture.Id);
        glBindTexture(GL_TEXTURE_2D, texture.Id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(pixels);

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
