#include <Common/Types.h>
#include <GL/glew.h>
#include <Engine/Graphics/Raw/Vertex.h>

class Sprite {
public:
    Sprite() : _x(0), _y(0), _width(0), _height(0), _vboId(0), _vaoId(0) {};
    ~Sprite() {
        if (_vaoId != 0) {
            glDeleteVertexArrays(1, &_vaoId);
        }
        if (_vboId != 0) {
            glDeleteBuffers(1, &_vboId);
        }
    };
    void Init(float x, float y, float width, float height) {
        _x = x;
        _y = y;
        _width = width;
        _height = height;

        Vertex vertexData[6];
        // Triangle 1
        vertexData[0].position.x = x + width;
        vertexData[0].position.y = y + height;
        vertexData[1].position.x = x;
        vertexData[1].position.y = y + height;
        vertexData[2].position.x = x;
        vertexData[2].position.y = y;
        // Triangle 2
        vertexData[3].position.x = x;
        vertexData[3].position.y = y;
        vertexData[4].position.x = x + width;
        vertexData[4].position.y = y;
        vertexData[5].position.x = x + width;
        vertexData[5].position.y = y + height;

        for (int i = 0; i < 6; i++) {
            vertexData[i].color.r = 255;
            vertexData[i].color.g = 0;
            vertexData[i].color.b = 255;
            vertexData[i].color.a = 255;
        }

        if (_vboId == 0) {
            glGenBuffers(1, &_vboId);
            CheckError();
        }

        if (_vaoId == 0) {
            glGenVertexArrays(1, &_vaoId);
            CheckError();
        }

        glBindVertexArray(_vaoId);
        CheckError();

        glBindBuffer(GL_ARRAY_BUFFER, _vboId);
        CheckError();
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
        CheckError();

        glEnableVertexAttribArray(0);
        CheckError();
        // This is the position attribute pointer
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        CheckError();

        glEnableVertexAttribArray(1);
        CheckError();
        // This is the color attribute pointer
        glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
        CheckError();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        CheckError();

        glBindVertexArray(0);
        CheckError();
    }

    void Draw() {

        glBindVertexArray(_vaoId);
        CheckError();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        CheckError();

        glBindVertexArray(0);
        CheckError();
    }

private:
    float _x;
    float _y;
    float _width;
    float _height;
    GLuint _vboId;
    GLuint _vaoId;

    void CheckError() {
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            auto errStr = std::string(reinterpret_cast<const char*>(glewGetErrorString(err)));
            LOG_WARN("graphics", "OpenGL error: {} - {}", std::to_string(err), errStr);
        }
    }
};
