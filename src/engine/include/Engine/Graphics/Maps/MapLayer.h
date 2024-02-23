#pragma once

#include <Common/Types.h>
#include <vector>

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <GL/glew.h>
#include "Common/Logging/Log.h"

namespace {
#define glCheck(x) do{x; glErrorCheck(__FILE__, __LINE__, #x);}while (false)
}

static inline void glErrorCheck(const char* file, unsigned int line, const char* expression) {
    //get the last error
    GLenum errorCode = glGetError();

    if (errorCode != GL_NO_ERROR)
    {
        std::string fileString = file;
        std::string error = "Unknown error";
        std::string description = "No description";

        //decode the error code
        switch (errorCode)
        {
            case GL_INVALID_ENUM:
            {
                error = "GL_INVALID_ENUM";
                description = "An unacceptable value has been specified for an enumerated argument.";
                break;
            }

            case GL_INVALID_VALUE:
            {
                error = "GL_INVALID_VALUE";
                description = "A numeric argument is out of range.";
                break;
            }

            case GL_INVALID_OPERATION:
            {
                error = "GL_INVALID_OPERATION";
                description = "The specified operation is not allowed in the current state.";
                break;
            }

            case GL_STACK_OVERFLOW:
            {
                error = "GL_STACK_OVERFLOW";
                description = "This command would cause a stack overflow.";
                break;
            }

            case GL_STACK_UNDERFLOW:
            {
                error = "GL_STACK_UNDERFLOW";
                description = "This command would cause a stack underflow.";
                break;
            }

            case GL_OUT_OF_MEMORY:
            {
                error = "GL_OUT_OF_MEMORY";
                description = "There is not enough memory left to execute the command.";
                break;
            }

        }
        LOG_DEBUG("opengl", "An internal OpenGL call failed in {} ({}). Expression: {}. Error description: {} {}", fileString.substr(fileString.find_last_of("\\/") + 1), line, expression, error, description);
    }
}

class MapLayer final {
public:
    MapLayer(const tmx::Map& map,std::size_t layerIdx, const std::vector<unsigned>& textures)
        : _tilesetTextures(textures) {
        CreateSubsets(map, layerIdx);
    }

    ~MapLayer() {
        for(auto& ss : _subsets)
        {
            if(ss.vbo)
            {
                glCheck(glDeleteBuffers(1, &ss.vbo));
            }
            if(ss.lookup)
            {
                glCheck(glDeleteTextures(1, &ss.lookup));
            }
            //don't delete the tileset textures as these are
            //shared and deleted elsewhere
        }
    }

    void Draw() {

        glCheck(glEnableVertexAttribArray(0));
        glCheck(glEnableVertexAttribArray(1));
        glCheck(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr));
        glCheck(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))));

        for(const auto& ss : _subsets)
        {
            glCheck(glActiveTexture(GL_TEXTURE0));
            glCheck(glBindTexture(GL_TEXTURE_2D, ss.texture));

            glCheck(glActiveTexture(GL_TEXTURE1));
            glCheck(glBindTexture(GL_TEXTURE_2D, ss.lookup));

            glCheck(glBindBuffer(GL_ARRAY_BUFFER, ss.vbo));
            glCheck(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
        }

        glCheck(glDisableVertexAttribArray(0));
        glCheck(glDisableVertexAttribArray(1));

    }

private:
    const std::vector<unsigned>& _tilesetTextures;

    struct Subset final {
        unsigned vbo = 0;
        unsigned texture = 0;
        unsigned lookup = 0;
    };
    std::vector<Subset> _subsets;

    void CreateSubsets(const tmx::Map& map, std::size_t layerIdx) {
        const auto &layers = map.getLayers();
        if (layerIdx >= layers.size() || (layers[layerIdx]->getType() != tmx::Layer::Type::Tile)) {
            LOG_WARN("map", "Invalid layer index or layer type, layer will be empty");
            return;
        }
        const auto layer = dynamic_cast<const tmx::TileLayer *>(layers[layerIdx].get());

        auto bounds = map.getBounds();
        float verts[] =
                {
                        bounds.left, bounds.top, 0.f, 0.f, 0.f,
                        bounds.left + bounds.width, bounds.top, 0.f, 1.f, 0.f,
                        bounds.left, bounds.top + bounds.height, 0.f, 0.f, 1.f,
                        bounds.left + bounds.width, bounds.top + bounds.height, 0.f, 1.f, 1.f
                };

        const auto &mapSize = map.getTileCount();
        const auto &tilesets = map.getTilesets();
        for (auto i = 0u; i < tilesets.size(); ++i) {
            //check each tile ID to see if it falls in the current tile set
            const auto &ts = tilesets[i];
            const auto &tileIDs = layer->getTiles();
            std::vector<std::uint16_t> pixelData;
            bool tsUsed = false;

            for (auto y = 0u; y < mapSize.y; ++y) {
                for (auto x = 0u; x < mapSize.x; ++x) {
                    auto idx = y * mapSize.x + x;
                    if (idx < tileIDs.size() && tileIDs[idx].ID >= ts.getFirstGID()
                        && tileIDs[idx].ID < (ts.getFirstGID() + ts.getTileCount())) {
                        pixelData.push_back(static_cast<std::uint16_t>((tileIDs[idx].ID - ts.getFirstGID()) +
                                                                       1)); //red channel - making sure to index relative to the tileset
                        pixelData.push_back(
                                static_cast<std::uint16_t>(tileIDs[idx].flipFlags)); //green channel - tile flips are performed on the shader
                        tsUsed = true;
                    } else {
                        //pad with empty space
                        pixelData.push_back(0);
                        pixelData.push_back(0);
                    }
                }
            }

            //if we have some data for this tile set, create the resources
            if (tsUsed) {
                _subsets.emplace_back();
                _subsets.back().texture = _tilesetTextures[i];

                glCheck(glGenBuffers(1, &_subsets.back().vbo));
                glCheck(glBindBuffer(GL_ARRAY_BUFFER, _subsets.back().vbo));
                glCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW));

                glCheck(glGenTextures(1, &_subsets.back().lookup));
                glCheck(glBindTexture(GL_TEXTURE_2D, _subsets.back().lookup));
                glCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16UI, mapSize.x, mapSize.y, 0, GL_RG_INTEGER,
                                     GL_UNSIGNED_SHORT, (void *) pixelData.data()));

                glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
                glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
                glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
                glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
            }
        }
    }
};
