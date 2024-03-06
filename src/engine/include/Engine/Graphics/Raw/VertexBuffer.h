#pragma once

#include <Common/Types.h>
#include <glad/glad.h>
#include <Engine/Graphics/Raw/OpenGLBuffer.h>

class VertexBuffer
{
public:
    VertexBuffer(U32 size)
    {
        glGenBuffers(1, &m_RendererId);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer(F32* vertices, U32 size)
    {
        glGenBuffers(1, &m_RendererId);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    ~VertexBuffer()
    {
        if (m_RendererId != 0)
        {
            glDeleteBuffers(1, &m_RendererId);
        }
    }

    void Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
    }

    void Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void SetData(const void* data, U32 size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
    [[nodiscard]] const BufferLayout& GetLayout() const { return m_Layout; }

    static Ref<VertexBuffer> Create(U32 size)
    {
        return CreateRef<VertexBuffer>(size);
    }
    static Ref<VertexBuffer> Create(F32* vertices, U32 size)
    {
        return CreateRef<VertexBuffer>(vertices, size);
    }

private:
    U32 m_RendererId;
    BufferLayout m_Layout;
};