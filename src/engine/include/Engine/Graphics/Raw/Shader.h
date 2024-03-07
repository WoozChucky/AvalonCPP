#pragma once

#include <Common/Types.h>
#include <Common/Logging/Log.h>
#include <glad/glad.h>
#include <fstream>

class Shader {
public:
    Shader(const std::string &filepath) {
        auto source = ReadFile(filepath);
        auto shaderSources = PreProcess(source);
        Compile(shaderSources);

        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);
    }

    Shader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) {
        std::unordered_map<GLenum, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);
    }

    ~Shader() {
        if (m_RendererId != 0) {
            glDeleteProgram(m_RendererId);
        }
    };

    void Bind() const {
        glUseProgram(m_RendererId);
    }

    void Unbind() const {
        glUseProgram(0);
    }

    const std::string &GetName() { return m_Name; }

    void SetInt(const std::string &name, int value) {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform1i(location, value);
    }

    void SetIntArray(const std::string &name, int *value, uint32_t count) {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform1iv(location, count, value);
    }

    void SetFloat(const std::string &name, float value) {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform1f(location, value);
    }

    void SetFloat2(const std::string &name, const glm::vec2 &value) {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void SetFloat3(const std::string &name, const glm::vec3 &value) {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void SetFloat4(const std::string &name, const glm::vec4 &value) {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void SetMat3(const std::string &name, const glm::mat3 &value) {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, &value[0][0]);
    }

    void SetMat4(const std::string &name, const glm::mat4 &value) {
        GLint location = glGetUniformLocation(m_RendererId, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
    }

    static Ref<Shader> Create(const std::string &filepath) {
        return CreateRef<Shader>(filepath);
    }

    static Ref<Shader> Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) {
        return CreateRef<Shader>(name, vertexSrc, fragmentSrc);
    }

private:
    static GLenum ShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;

        throw std::runtime_error("Unknown shader type!");
    }

    std::string ReadFile(const std::string &filepath)
    {
        std::string result;
        std::ifstream file(filepath, std::ios::binary);
        if (!file)
        {
            LOG_ERROR("Shader", "Could not open file '{}'", filepath);
            return result;
        }

        file.seekg(0, std::ios::end);
        result.resize(file.tellg());
        file.seekg(0, std::ios::beg);

        file.read(&result[0], result.size());
        file.close();

        return result;
    }

    std::unordered_map<U32, std::string> PreProcess(const std::string &source)
    {
        std::unordered_map<GLenum, std::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = source.find(typeToken, 0);
        while (pos != std::string::npos)
        {
            size_t eol = source.find_first_of("\r\n", pos);
            if (eol != std::string::npos)
            {
                throw std::runtime_error("Syntax error");
            }
            size_t begin = pos + typeTokenLength + 1;
            std::string type = source.substr(begin, eol - begin);
            if (!ShaderTypeFromString(type))
            {
                throw std::runtime_error("Invalid shader type specified");
            }

            size_t nextLinePos = source.find_first_not_of("\r\n", eol);
            pos = source.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
        }

        return shaderSources;
    }

    void Compile(const std::unordered_map<U32, std::string>& shaderSources)
    {
        GLuint program = glCreateProgram();
        std::array<GLenum, 2> glShaderIDs;
        int glShaderIDIndex = 0;
        for (auto& kv : shaderSources)
        {
            GLenum type = kv.first;
            const std::string& source = kv.second;

            GLuint shader = glCreateShader(type);

            const GLchar* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            // Compile the vertex shader
            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                // The maxLength includes the NULL character
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                // We don't need the shader anymore.
                glDeleteShader(shader);

                LOG_WARN("Shader", "Shader compilation failure: {0}", infoLog.data());
                throw std::runtime_error("Shader compilation failure!");
                return;
            }

            glAttachShader(program, shader);
            glShaderIDs[glShaderIDIndex++] = shader;
        }

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            for (auto id : glShaderIDs)
            {
                glDeleteShader(id);
            }

            LOG_WARN("Shader", "Shader link failure: {0}", infoLog.data());
            throw std::runtime_error("Shader link failure!");
            return;
        }

        // Always detach shaders after a successful link.
        for (auto id : glShaderIDs)
        {
            glDetachShader(program, id);
        }

        m_RendererId = program;
    }

private:
    std::string m_Name;
    U32 m_RendererId;
};
