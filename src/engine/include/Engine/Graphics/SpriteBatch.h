#pragma once

#include <Common/Types.h>
#include <Common/Logging/Log.h>
#include <GL/glew.h>
#include <vector>
#include <Engine/Graphics/Raw/Vertex.h>
#include <glm/glm.hpp>

enum class GlyphSortType
{
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE
};

struct Glyph
{
    GLuint Texture;
    F32 Depth;

    Vertex TopLeft;
    Vertex BottomLeft;
    Vertex TopRight;
    Vertex BottomRight;
};

class RenderBatch
{
public:
    RenderBatch(GLuint offset, GLuint numVertices, GLuint texture) : Offset(offset), NumVertices(numVertices), Texture(texture) {}
    GLuint Offset;
    GLuint NumVertices;
    GLuint Texture;
};

class SpriteBatch
{
public:
    SpriteBatch() {
        _vbo = 0;
        _vao = 0;
    }
    ~SpriteBatch() {
        if (_vbo != 0) {
            glDeleteBuffers(1, &_vbo);
        }
        if (_vao != 0) {
            glDeleteVertexArrays(1, &_vao);
        }
    }
    void Initialize() {
        CreateVertexArray();
    }

    void Begin(GlyphSortType sortType = GlyphSortType::TEXTURE) {
        _sortType = sortType;
        _renderBatches.clear();
        for (auto* glyph : _glyphs) {
            delete glyph;
        }
        _glyphs.clear();
    }

    void End() {
        SortGlyphs();
        CreateRenderBatches();
    }

    void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, F32 depth, const ColorRGBA8& color) {
        auto* glyph = new Glyph();
        glyph->Texture = texture;
        glyph->Depth = depth;

        glyph->TopLeft.SetColor(color.r, color.g, color.b, color.a);
        glyph->TopLeft.SetPosition(destRect.x, destRect.y + destRect.w);
        glyph->TopLeft.SetTextureCoordinate(uvRect.x, uvRect.y + uvRect.w);

        glyph->BottomLeft.SetColor(color.r, color.g, color.b, color.a);
        glyph->BottomLeft.SetPosition(destRect.x, destRect.y);
        glyph->BottomLeft.SetTextureCoordinate(uvRect.x, uvRect.y);

        glyph->TopRight.SetColor(color.r, color.g, color.b, color.a);
        glyph->TopRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
        glyph->TopRight.SetTextureCoordinate(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

        glyph->BottomRight.SetColor(color.r, color.g, color.b, color.a);
        glyph->BottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
        glyph->BottomRight.SetTextureCoordinate(uvRect.x + uvRect.z, uvRect.y);

        _glyphs.push_back(glyph);
    }

    void Render() {

        glBindVertexArray(_vao);

        for (U32 rb = 0; rb < _renderBatches.size(); rb++) {
            glBindTexture(GL_TEXTURE_2D, _renderBatches[rb].Texture);
            glDrawArrays(GL_TRIANGLES, _renderBatches[rb].Offset, _renderBatches[rb].NumVertices);
        }

        glBindVertexArray(0);

    }

private:
    void CreateRenderBatches () {
        std::vector<Vertex> vertices;
        vertices.resize(_glyphs.size() * 6);

        if (_glyphs.empty()) {
            return;
        }

        GLuint offset = 0;
        GLuint currentVertex = 0;
        _renderBatches.emplace_back(offset, 6, _glyphs[0]->Texture);
        vertices[currentVertex++] = _glyphs[0]->TopLeft;
        vertices[currentVertex++] = _glyphs[0]->BottomLeft;
        vertices[currentVertex++] = _glyphs[0]->BottomRight;
        vertices[currentVertex++] = _glyphs[0]->BottomRight;
        vertices[currentVertex++] = _glyphs[0]->TopRight;
        vertices[currentVertex++] = _glyphs[0]->TopLeft;
        offset += 6;

        for (U32 cg = 1; cg < _glyphs.size(); cg++) {
            if (_glyphs[cg]->Texture != _glyphs[cg - 1]->Texture) {
                _renderBatches.emplace_back(offset, 6, _glyphs[cg]->Texture);
            } else {
                _renderBatches.back().NumVertices += 6;
            }
            vertices[currentVertex++] = _glyphs[cg]->TopLeft;
            vertices[currentVertex++] = _glyphs[cg]->BottomLeft;
            vertices[currentVertex++] = _glyphs[cg]->BottomRight;
            vertices[currentVertex++] = _glyphs[cg]->BottomRight;
            vertices[currentVertex++] = _glyphs[cg]->TopRight;
            vertices[currentVertex++] = _glyphs[cg]->TopLeft;
            offset += 6;
        }

        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void CreateVertexArray() {
        if (_vao == 0) {
            glGenVertexArrays(1, &_vao);
        }
        glBindVertexArray(_vao);

        if (_vbo == 0) {
            glGenBuffers(1, &_vbo);
        }
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinate));

        //glDisableVertexAttribArray(0);
        //glDisableVertexAttribArray(1);
        //glDisableVertexAttribArray(2);

        glBindVertexArray(0);
    }

    static bool CompareFrontToBack(Glyph* a, Glyph* b) {
        return a->Depth < b->Depth;
    }

    static bool CompareBackToFront(Glyph* a, Glyph* b) {
        return a->Depth > b->Depth;
    }

    static bool CompareTexture(Glyph* a, Glyph* b) {
        return a->Texture < b->Texture;
    }

    void SortGlyphs() {
        switch (_sortType) {
        case GlyphSortType::FRONT_TO_BACK:
            std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareFrontToBack);
            break;
        case GlyphSortType::BACK_TO_FRONT:
            std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareBackToFront);
            break;
        case GlyphSortType::TEXTURE:
            std::stable_sort(_glyphs.begin(), _glyphs.end(), CompareTexture);
            break;
        }
    }

    GlyphSortType _sortType;
    std::vector<Glyph*> _glyphs;
    std::vector<RenderBatch> _renderBatches;
    GLuint _vbo;
    GLuint _vao;
};
