#include <Common/Types.h>
#include <GL/glew.h>

class Sprite {
public:
    Sprite() = default;
    ~Sprite() {
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
        vertexData[0] = x + width;
        vertexData[1] = y + height;
        vertexData[2] = x;
        vertexData[3] = y + height;
        vertexData[4] = x;
        vertexData[5] = y;
        vertexData[6] = x;
        vertexData[7] = y;
        vertexData[8] = x + width;
        vertexData[9] = y;
        vertexData[10] = x + width;
        vertexData[11] = y + height;

        if (_vboId == 0) {
            glGenBuffers(1, &_vboId);
        }

        glBindBuffer(GL_ARRAY_BUFFER, _vboId);
        glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), vertexData, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Draw() {

        glBindBuffer(GL_ARRAY_BUFFER, _vboId);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

private:
    float _x;
    float _y;
    float _width;
    float _height;
    U32 _vboId;
};