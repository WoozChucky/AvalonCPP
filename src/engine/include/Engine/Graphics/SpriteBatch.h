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

class Glyph
{
public:
    Glyph() {}
    Glyph(GLuint texture, F32 depth, ColorRGBA8 color, const glm::vec4& destRect, const glm::vec4& uvRect) {

        Texture = texture;
        Depth = depth;

        TopLeft.SetColor(color.r, color.g, color.b, color.a);
        TopLeft.SetPosition(destRect.x, destRect.y + destRect.w);
        TopLeft.SetTextureCoordinate(uvRect.x, uvRect.y + uvRect.w);

        BottomLeft.SetColor(color.r, color.g, color.b, color.a);
        BottomLeft.SetPosition(destRect.x, destRect.y);
        BottomLeft.SetTextureCoordinate(uvRect.x, uvRect.y);

        TopRight.SetColor(color.r, color.g, color.b, color.a);
        TopRight.SetPosition(destRect.x + destRect.z, destRect.y + destRect.w);
        TopRight.SetTextureCoordinate(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

        BottomRight.SetColor(color.r, color.g, color.b, color.a);
        BottomRight.SetPosition(destRect.x + destRect.z, destRect.y);
        BottomRight.SetTextureCoordinate(uvRect.x + uvRect.z, uvRect.y);
    }

    Glyph(GLuint texture, F32 depth, ColorRGBA8 color, const glm::vec4& destRect, const glm::vec4& uvRect, float angle) {

        Texture = texture;
        Depth = depth;

        glm::vec2 halfDimensions(destRect.z / 2.0f, destRect.w / 2.0f);

        // Get points centered at origin
        glm::vec2 topLeft(-halfDimensions.x, halfDimensions.y);
        glm::vec2 bottomLeft(-halfDimensions.x, -halfDimensions.y);
        glm::vec2 topRight(halfDimensions.x, halfDimensions.y);
        glm::vec2 bottomRight(halfDimensions.x, -halfDimensions.y);

        // Rotate the points
        topLeft = rotatePoint(topLeft, angle) + halfDimensions;
        bottomLeft = rotatePoint(bottomLeft, angle) + halfDimensions;
        topRight = rotatePoint(topRight, angle) + halfDimensions;
        bottomRight = rotatePoint(bottomRight, angle) + halfDimensions;

        TopLeft.SetColor(color.r, color.g, color.b, color.a);
        TopLeft.SetPosition(destRect.x + topLeft.x, destRect.y + topLeft.y);
        TopLeft.SetTextureCoordinate(uvRect.x, uvRect.y + uvRect.w);

        BottomLeft.SetColor(color.r, color.g, color.b, color.a);
        BottomLeft.SetPosition(destRect.x + bottomLeft.x, destRect.y + bottomLeft.y);
        BottomLeft.SetTextureCoordinate(uvRect.x, uvRect.y);

        TopRight.SetColor(color.r, color.g, color.b, color.a);
        TopRight.SetPosition(destRect.x + topRight.x, destRect.y + topRight.y);
        TopRight.SetTextureCoordinate(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

        BottomRight.SetColor(color.r, color.g, color.b, color.a);
        BottomRight.SetPosition(destRect.x + bottomRight.x, destRect.y + bottomRight.y);
        BottomRight.SetTextureCoordinate(uvRect.x + uvRect.z, uvRect.y);
    }

    GLuint Texture;
    F32 Depth;

    Vertex TopLeft;
    Vertex BottomLeft;
    Vertex TopRight;
    Vertex BottomRight;

private:
    glm::vec2 rotatePoint(glm::vec2 pos, F32 angle) {
        glm::vec2 newv;
        newv.x = pos.x * cos(angle) - pos.y * sin(angle);
        newv.y = pos.x * sin(angle) + pos.y * cos(angle);
        return newv;
    }
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
        _glyphs.clear();
    }

    void End() {
        _glyphPtrs.resize(_glyphs.size());
        for (U32 idx = 0; idx < _glyphs.size(); idx++) {
            _glyphPtrs[idx] = &_glyphs[idx];
        }
        SortGlyphs();
        CreateRenderBatches();
    }

    void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, F32 depth, const ColorRGBA8& color) {
        _glyphs.emplace_back(texture, depth, color, destRect, uvRect);
    }

    void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, F32 depth, const ColorRGBA8& color, F32 angle) {
        _glyphs.emplace_back(texture, depth, color, destRect, uvRect, angle);
    }

    void Draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, F32 depth, const ColorRGBA8& color, const glm::vec2& direction) {
        const glm::vec2 right(1.0f, 0.0f);
        F32 angle = acos(glm::dot(right, direction));
        _glyphs.emplace_back(texture, depth, color, destRect, uvRect, angle);
    }

    void Render() {

        glBindVertexArray(_vao);

        for (auto & _renderBatch : _renderBatches) {
            glBindTexture(GL_TEXTURE_2D, _renderBatch.Texture);
            glDrawArrays(GL_TRIANGLES, _renderBatch.Offset, _renderBatch.NumVertices);
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
        _renderBatches.emplace_back(offset, 6, _glyphPtrs[0]->Texture);
        vertices[currentVertex++] = _glyphPtrs[0]->TopLeft;
        vertices[currentVertex++] = _glyphPtrs[0]->BottomLeft;
        vertices[currentVertex++] = _glyphPtrs[0]->BottomRight;
        vertices[currentVertex++] = _glyphPtrs[0]->BottomRight;
        vertices[currentVertex++] = _glyphPtrs[0]->TopRight;
        vertices[currentVertex++] = _glyphPtrs[0]->TopLeft;
        offset += 6;

        for (U32 cg = 1; cg < _glyphs.size(); cg++) {
            if (_glyphPtrs[cg]->Texture != _glyphPtrs[cg - 1]->Texture) {
                _renderBatches.emplace_back(offset, 6, _glyphPtrs[cg]->Texture);
            } else {
                _renderBatches.back().NumVertices += 6;
            }
            vertices[currentVertex++] = _glyphPtrs[cg]->TopLeft;
            vertices[currentVertex++] = _glyphPtrs[cg]->BottomLeft;
            vertices[currentVertex++] = _glyphPtrs[cg]->BottomRight;
            vertices[currentVertex++] = _glyphPtrs[cg]->BottomRight;
            vertices[currentVertex++] = _glyphPtrs[cg]->TopRight;
            vertices[currentVertex++] = _glyphPtrs[cg]->TopLeft;
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
            std::stable_sort(_glyphPtrs.begin(), _glyphPtrs.end(), CompareFrontToBack);
            break;
        case GlyphSortType::BACK_TO_FRONT:
            std::stable_sort(_glyphPtrs.begin(), _glyphPtrs.end(), CompareBackToFront);
            break;
        case GlyphSortType::TEXTURE:
            std::stable_sort(_glyphPtrs.begin(), _glyphPtrs.end(), CompareTexture);
            break;
        }
    }

    GlyphSortType _sortType;
    std::vector<Glyph*> _glyphPtrs;
    std::vector<Glyph> _glyphs;
    std::vector<RenderBatch> _renderBatches;
    GLuint _vbo;
    GLuint _vao;
};
