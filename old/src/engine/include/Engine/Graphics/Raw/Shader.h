#pragma once

#include <Common/Types.h>
#include <GL/glew.h>
#include <fstream>

class Shader {
public:
    Shader() : _program(0), _vertexShaderId(0), _fragmentShaderId(0), _numAttributes(0) {}
    ~Shader() {
        if (_program != 0) {
            glDeleteProgram(_program);
        }
    };

    void InitFromSource(const char* vertexShader, const char* fragmentShader) {
        if (_program != 0 || _vertexShaderId != 0 || _fragmentShaderId != 0)
            throw std::runtime_error("Shader already initialized");
        _vertexShaderId = Compile(vertexShader, GL_VERTEX_SHADER);
        _fragmentShaderId = Compile(fragmentShader, GL_FRAGMENT_SHADER);
        _program = CreateProgram(_vertexShaderId, _fragmentShaderId);
    }

    void Init(const std::string& vertexShader, const std::string& fragmentShader) {
        if (_program != 0 || _vertexShaderId != 0 || _fragmentShaderId != 0)
            throw std::runtime_error("Shader already initialized");
        LoadShaders(vertexShader.c_str(), fragmentShader.c_str());
        _program = CreateProgram(_vertexShaderId, _fragmentShaderId);
    }

    void AddAttribute(const std::string& attributeName) {
        if (_vertexShaderId == 0 || _fragmentShaderId == 0)
            throw std::runtime_error("Shader not initialized");
        glBindAttribLocation(_program, _numAttributes++, attributeName.c_str());
        CheckError();
    }

    GLint GetUniformLocation(const std::string& uniformName) const {
        if (_program == 0)
            throw std::runtime_error("Shader not initialized");
        auto location = glGetUniformLocation(_program, uniformName.c_str());
        if (location == GL_INVALID_INDEX)
            throw std::runtime_error("Uniform " + uniformName + " not found in shader");
        return location;
    }

    void Link() {
        if (_program == 0)
            throw std::runtime_error("Shader is not initialized");
        Link(_vertexShaderId, _fragmentShaderId);
    }

    void Bind() {
        if (_program == 0)
            throw std::runtime_error("Shader not initialized");
        glUseProgram(_program);
        CheckError();
        for (U32 i = 0; i < _numAttributes; i++) {
            glEnableVertexAttribArray(i);
            CheckError();
        }
    }

    void Unbind() {
        if (_program == 0)
            throw std::runtime_error("Shader not initialized");
        glUseProgram(0);
        CheckError();
        for (U32 i = 0; i < _numAttributes; i++) {
            glDisableVertexAttribArray(i);
            CheckError();
        }
    }
private:
    GLuint _program;
    GLuint _vertexShaderId;
    GLuint _fragmentShaderId;
    U32 _numAttributes;

    GLuint Compile(const char* shaderCode, GLenum type) {
        GLuint shaderId = glCreateShader(type);
        CheckError();
        glShaderSource(shaderId, 1, &shaderCode, nullptr);
        CheckError();
        glCompileShader(shaderId);
        CheckError();

        GLint result;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
        CheckError();
        if (result == GL_FALSE) {
            GLint length;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(shaderId, length, &length, &error[0]);
            glDeleteShader(shaderId);
            LOG_ERROR("graphics", "Failed to compile shader: {}", std::string(error.begin(), error.end()));
            throw std::runtime_error("Failed to compile shader: " + std::string(error.begin(), error.end()));
        }
        return shaderId;
    }

    GLuint CreateProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
    {
        GLuint program = glCreateProgram();
        CheckError();
        glAttachShader(program, vertexShaderId);
        CheckError();
        glAttachShader(program, fragmentShaderId);
        CheckError();
        return program;
    }

    void Link(GLuint vertexShaderId, GLuint fragmentShaderId) {
        glLinkProgram(_program);
        CheckError();

        GLint result;
        glGetProgramiv(_program, GL_LINK_STATUS, &result);
        CheckError();
        if (result == GL_FALSE) {
            GLint length;
            glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetProgramInfoLog(_program, length, &length, &error[0]);
            glDeleteProgram(_program);
            throw std::runtime_error("Failed to link program: " + std::string(error.begin(), error.end()));
        }

        glDetachShader(_program, vertexShaderId);
        CheckError();
        glDetachShader(_program, fragmentShaderId);
        CheckError();
        glDeleteShader(vertexShaderId);
        CheckError();
        glDeleteShader(fragmentShaderId);
        CheckError();
    }

    void LoadShaders(const char* vertexShaderPath, const char* fragmentShaderPath) {
        std::fstream vertexFile(vertexShaderPath, std::ios::in);
        std::fstream fragmentFile(fragmentShaderPath, std::ios::in);

        if (!vertexFile.is_open()) {
            throw std::runtime_error("Failed to open vertex shader file: " + std::string(vertexShaderPath));
        }

        if (!fragmentFile.is_open()) {
            throw std::runtime_error("Failed to open fragment shader file: " + std::string(fragmentShaderPath));
        }

        std::string vertexShader((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
        std::string fragmentShader((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());

        vertexFile.close();
        fragmentFile.close();

        const char* vertexShaderCStr = vertexShader.c_str();
        const char* fragmentShaderCStr = fragmentShader.c_str();

        _vertexShaderId = Compile(vertexShaderCStr, GL_VERTEX_SHADER);
        _fragmentShaderId = Compile(fragmentShaderCStr, GL_FRAGMENT_SHADER);
    }

    void CheckError() {
        GLenum err;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            auto errStr = std::string(reinterpret_cast<const char*>(glewGetErrorString(err)));
            LOG_WARN("graphics", "OpenGL error: {} - {}", std::to_string(err), errStr);
        }
    }
};
