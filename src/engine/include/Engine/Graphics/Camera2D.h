#pragma once

#include <Common/Types.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D {
public:
    Camera2D() : _needsMatrixUpdate(true), _scale(1.0f), _position(0.0f, 0.0f), _cameraMatrix(1.0f), _orthoMatrix(1.0f) {}

    void Init(U32 screenWidth, U32 screenHeight) {
        _screenWidth = screenWidth;
        _screenHeight = screenHeight;
        _orthoMatrix = glm::ortho(0.0f, (F32)_screenWidth, 0.0f, (F32)_screenHeight, -0.1f, 100.f);
    }

    void Update() {
        if (_needsMatrixUpdate) {
            // Update camera translation
            glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
            _cameraMatrix = glm::translate(_orthoMatrix, translate);

            // Update camera scale
            glm::vec3 scale(_scale, _scale, 0.0f);
            _cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _cameraMatrix;
            _needsMatrixUpdate = false;
        }
    }

    glm::vec2 ConvertScreenToWorld(glm::vec2 screenCoords) {
        screenCoords.y = _screenHeight - screenCoords.y;
        screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
        screenCoords /= _scale;
        screenCoords += _position;
        return screenCoords;
    }

    bool IsBoxInView(const glm::vec2& position, const glm::vec2& dimensions) {
        glm::vec2 scaledScreenDimensions = glm::vec2(_screenWidth, _screenHeight) / _scale;

        const F32 MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
        const F32 MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

        glm::vec2 centerPos = position + dimensions / 2.0f;
        glm::vec2 distVec = centerPos - _position;

        F32 xDepth = MIN_DISTANCE_X - abs(distVec.x);
        F32 yDepth = MIN_DISTANCE_Y - abs(distVec.y);

        return xDepth > 0 && yDepth > 0;
    }

    void SetPosition(const glm::vec2& newPosition) {
        _position = newPosition;
        _needsMatrixUpdate = true;
    }

    void SetScale(F32 newScale) {
        _scale = newScale;
        _needsMatrixUpdate = true;
    }

    glm::vec2 GetPosition() const {
        return _position;
    }

    F32 GetScale() const {
        return _scale;
    }

    glm::mat4 GetCameraMatrix() const {
        return _cameraMatrix;
    }

private:
    U32 _screenWidth, _screenHeight;
    bool _needsMatrixUpdate;
    F32 _scale;
    glm::vec2 _position;
    glm::mat4 _cameraMatrix;
    glm::mat4 _orthoMatrix;
};
