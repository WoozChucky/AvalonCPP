#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Common/Types.h"
#include "Engine/Graphics/Raw/Vertex.h"
#include "Engine/Graphics/Raw/Shader.h"

namespace DebugRendererShader {

const char DEBUG_VERT[] = R"(
#version 410

in vec2 position;
in vec4 color;

out vec4 fragmentColor;
out vec2 fragmentPosition;

uniform mat4 projection;

void main() {
    // Set x and y to the position of the vertex
    gl_Position.xy = (projection * vec4(position, 0.0, 1.0)).xy ;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0; // indicates that it is normalized
    // Set the color of the vertex
    fragmentColor = color;
    fragmentPosition = position;
}
)";

const char DEBUG_FRAG[] = R"(
#version 410

in vec2 fragmentPosition;
in vec4 fragmentColor;

out vec4 color;

void main() {
    color = fragmentColor;
}
)";
}



class DebugRenderer {
public:
    DebugRenderer() = default;
    ~DebugRenderer() {
        Dispose();
    }

    void Init() {

        _shader.InitFromSource(DebugRendererShader::DEBUG_VERT, DebugRendererShader::DEBUG_FRAG);
        _shader.AddAttribute("position");
        _shader.AddAttribute("color");
        _shader.Link();

        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &_vbo);
        glGenBuffers(1, &_ibo);

        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, Position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(DebugVertex), (void*)offsetof(DebugVertex, Color));

        glBindVertexArray(0);

    }

    void End() {
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(DebugVertex), nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, _vertices.size() * sizeof(DebugVertex), _vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(U32), nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, _indices.size() * sizeof(U32), _indices.data());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        _numElements = _indices.size();
        _indices.clear();
        _vertices.clear();
    }

    void DrawBox(const glm::vec4& destRect, const ColorRGBA8& color, F32 angle) {

        auto idx = _vertices.size();
        _vertices.resize(_vertices.size() + 4);

        glm::vec2 halfDimensions(destRect.z / 2.0f, destRect.w / 2.0f);

        // Get points centered at origin
        glm::vec2 topLeft(-halfDimensions.x, halfDimensions.y);
        glm::vec2 bottomLeft(-halfDimensions.x, -halfDimensions.y);
        glm::vec2 topRight(halfDimensions.x, halfDimensions.y);
        glm::vec2 bottomRight(halfDimensions.x, -halfDimensions.y);

        glm::vec2 positionOffset(destRect.x, destRect.y);

        // Rotate the points
        _vertices[idx].Position = rotatePoint(topLeft, angle) + halfDimensions + positionOffset;
        _vertices[idx].Color = color;

        _vertices[idx + 1].Position = rotatePoint(bottomLeft, angle) + halfDimensions + positionOffset;
        _vertices[idx + 1].Color = color;

        _vertices[idx + 2].Position = rotatePoint(bottomRight, angle) + halfDimensions + positionOffset;
        _vertices[idx + 2].Color = color;

        _vertices[idx + 3].Position = rotatePoint(topRight, angle) + halfDimensions + positionOffset;
        _vertices[idx + 3].Color = color;

        _indices.reserve(_indices.size() + 8);

        _indices.push_back(idx);
        _indices.push_back(idx + 1);

        _indices.push_back(idx + 1);
        _indices.push_back(idx + 2);

        _indices.push_back(idx + 2);
        _indices.push_back(idx + 3);

        _indices.push_back(idx + 3);
        _indices.push_back(idx);
    }

    void DrawCircle(const glm::vec2& center, const ColorRGBA8& color, F32 radius) {

        static const int NUM_VERTS = 100;
        static const F32 TWO_PI = 3.14159f * 2.0f;

        auto idx = _vertices.size();
        _vertices.resize(_vertices.size() + NUM_VERTS);

        for (int i = 0; i < NUM_VERTS; i++) {
            F32 angle = TWO_PI / NUM_VERTS * i;
            _vertices[idx + i].Position.x = center.x + cos(angle) * radius;
            _vertices[idx + i].Position.y = center.y + sin(angle) * radius;
            _vertices[idx + i].Color = color;
        }

        _indices.reserve(_indices.size() + NUM_VERTS * 2);
        for (int i = 0; i < NUM_VERTS - 1; i++) {
            _indices.push_back(idx + i);
            _indices.push_back(idx + i + 1);
        }
        _indices.push_back(idx + NUM_VERTS - 1);
        _indices.push_back(idx);

    }

    void Render(const glm::mat4 &projectionMatrix, F32 lineWidth = 1.0f) {

        _shader.Bind();

        auto projectionLocation = _shader.GetUniformLocation("projection");
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projectionMatrix[0][0]);

        glLineWidth(lineWidth);
        glBindVertexArray(_vao);
        glDrawElements(GL_LINES, _numElements, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        _shader.Unbind();
    }

    void Dispose() {
        if (_vao != 0) {
            glDeleteVertexArrays(1, &_vao);
            _vao = 0;
        }
        if (_vbo != 0) {
            glDeleteBuffers(1, &_vbo);
            _vbo = 0;
        }
        if (_ibo != 0) {
            glDeleteBuffers(1, &_ibo);
            _ibo = 0;
        }
    }

    struct DebugVertex {
        glm::vec2 Position;
        ColorRGBA8 Color;
    };

private:
    Shader _shader;
    std::vector<DebugVertex> _vertices;
    std::vector<U32> _indices;
    U32 _vbo = 0;
    U32 _vao = 0;
    U32 _ibo = 0;
    U32 _numElements = 0;

    glm::vec2 rotatePoint(glm::vec2 pos, F32 angle) {
        glm::vec2 newv;
        newv.x = pos.x * cos(angle) - pos.y * sin(angle);
        newv.y = pos.x * sin(angle) + pos.y * cos(angle);
        return newv;
    }
};
