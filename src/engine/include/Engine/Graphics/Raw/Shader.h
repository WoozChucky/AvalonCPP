#include <Common/Types.h>
#include <GL/glew.h>
#include <fstream>

class Shader {
public:
    Shader() = default;
    ~Shader() {
        if (_program != 0) {
            glDeleteProgram(_program);
        }
    };
    void Init(const std::string& vertexShader, const std::string& fragmentShader) {
        if (_program != 0 || _vertexShaderId != 0 || _fragmentShaderId != 0)
            throw std::runtime_error("Shader already initialized");
        LoadShaders(vertexShader.c_str(), fragmentShader.c_str());
    }

    void AddAttribute(const std::string& attributeName) {
        if (_vertexShaderId == 0 || _fragmentShaderId == 0)
            throw std::runtime_error("Shader not initialized");
        glBindAttribLocation(_program, _numAttributes++, attributeName.c_str());
    }

    void Link() {
        if (_program != 0)
            throw std::runtime_error("Shader already initialized");
        _program = Link(_vertexShaderId, _fragmentShaderId);
    }

    void Bind() {
        if (_program == 0)
            throw std::runtime_error("Shader not initialized");
        glUseProgram(_program);
    }

    void Unbind() {
        if (_program == 0)
            throw std::runtime_error("Shader not initialized");
        glUseProgram(0);
    }
private:
    GLuint _program;
    GLuint _vertexShaderId;
    GLuint _fragmentShaderId;
    U32 _numAttributes;

    GLuint Compile(const char* shaderCode, GLenum type) {
        GLuint shaderId = glCreateShader(type);
        glShaderSource(shaderId, 1, &shaderCode, nullptr);
        glCompileShader(shaderId);

        GLint result;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            GLint length;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetShaderInfoLog(shaderId, length, &length, &error[0]);
            glDeleteShader(shaderId);
            throw std::runtime_error("Failed to compile shader: " + std::string(error.begin(), error.end()));
        }
        return shaderId;
    }

    GLuint Link(GLuint vertexShaderId, GLuint fragmentShaderId) {
        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShaderId);
        glAttachShader(program, fragmentShaderId);

        glLinkProgram(program);

        GLint result;
        glGetProgramiv(program, GL_LINK_STATUS, &result);
        if (result == GL_FALSE) {
            GLint length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> error(length);
            glGetProgramInfoLog(program, length, &length, &error[0]);
            glDeleteProgram(program);
            throw std::runtime_error("Failed to link program: " + std::string(error.begin(), error.end()));
        }

        glDetachShader(program, vertexShaderId);
        glDetachShader(program, fragmentShaderId);
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        return program;
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
};