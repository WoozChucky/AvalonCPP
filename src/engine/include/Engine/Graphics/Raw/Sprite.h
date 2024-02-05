#include <Common/Types.h>
#include <GL/glew.h>

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

        float vertexData[12];
        // Triangle 1
        vertexData[0] = x + width;
        vertexData[1] = y + height;
        vertexData[2] = x;
        vertexData[3] = y + height;
        vertexData[4] = x;
        vertexData[5] = y;
        // Triangle 2
        vertexData[6] = x;
        vertexData[7] = y;
        vertexData[8] = x + width;
        vertexData[9] = y;
        vertexData[10] = x + width;
        vertexData[11] = y + height;

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
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
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
