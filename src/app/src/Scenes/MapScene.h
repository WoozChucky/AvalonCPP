#pragma once

#include "Scene.h"
#include "Engine/Graphics/Camera2D.h"

class MapScene : public IScene {
public:
    MapScene() = default;
    ~MapScene() override = default;

    void Initialize(U32 width, U32 height) override {
        _camera.Init(width, height);

        loadMap();
    }

    void Update(F32 deltaTime) override {
        _camera.Update();
    }

    void Draw(F32 deltaTime) override {

    }

    void Shutdown() override {
        for (auto& layer : m_mapLayers) {
            delete layer;
        }
        m_mapLayers.clear();
    }

private:
    Camera2D _camera;
    SpriteBatch _spriteBatch;
    std::vector<MapLayer*> m_mapLayers;
    std::vector<unsigned> m_tileTextures;

    void LoadTexture(const std::string& path) {
        m_tileTextures.emplace_back(0);
        auto& texture = m_tileTextures.back();

        texture = sAssetManager->GetTexture(TexturesName::Map, true).Id;
    }

    void loadMap() {
        tmx::Map map;
        map.load("Assets/Tutorial.tmx");

        const auto& tilesets = map.getTilesets();
        for(const auto& ts : tilesets)
        {
            LoadTexture(ts.getImagePath());
        }

        //create a drawable object for each tile layer
        const auto& layers = map.getLayers();
        for(auto i = 0u; i < layers.size(); ++i)
        {
            if(layers[i]->getType() == tmx::Layer::Type::Tile)
            {
                m_mapLayers.emplace_back(new MapLayer(map, i, m_tileTextures));
            }
        }
    }
};
