#include <Common/Types.h>
#include <glad/glad.h>
#include <Engine/Graphics/Raw/Vertex.h>
#include <Engine/Graphics/Raw/Texture.h>
#include <Engine/Graphics/AssetManager.h>

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
    void Init(float x, float y, float width, float height, TexturesName textureName) {
        _x = x;
        _y = y;
        _width = width;
        _height = height;
        _texture = sAssetManager->GetTexture(textureName);

        Vertex vertexData[6];
        // Triangle 1
        vertexData[0].SetPosition(x + width, y + height);
        vertexData[0].SetTextureCoordinate(1.0f, 1.0f);
        vertexData[1].SetPosition(x, y + height);
        vertexData[1].SetTextureCoordinate(0.0f, 1.0f);
        vertexData[2].SetPosition(x, y);
        vertexData[2].SetTextureCoordinate(0.0f, 0.0f);
        // Triangle 2
        vertexData[3].SetPosition(x, y);
        vertexData[3].SetTextureCoordinate(0.0f, 0.0f);
        vertexData[4].SetPosition(x + width, y);
        vertexData[4].SetTextureCoordinate(1.0f, 0.0f);
        vertexData[5].SetPosition(x + width, y + height);
        vertexData[5].SetTextureCoordinate(1.0f, 1.0f);

        for (int i = 0; i < 6; i++) {
            vertexData[i].SetColor(255, 0, 255, 255);
        }

        vertexData[1].SetColor(0, 0, 255, 255);
        vertexData[4].SetColor(0, 255, 0, 255);

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

        glEnableVertexAttribArray(2);
        CheckError();
        // This is the texture coordinate attribute pointer
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinate));
        CheckError();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        CheckError();

        glBindVertexArray(0);
        CheckError();
    }

    void Draw() {

        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _texture.Id);
        CheckError();

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
    Texture _texture;

    void CheckError() {
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            LOG_WARN("graphics", "OpenGL error: {}", std::to_string(err));
        }
    }
};
