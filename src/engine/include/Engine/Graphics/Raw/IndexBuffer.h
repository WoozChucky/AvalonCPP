#pragma once

#include <Common/Types.h>
#include <glad/glad.h>

class IndexBuffer
{
public:
    IndexBuffer(U32* indices, U32 count)
        : m_Count(count)
    {
        glGenBuffers(1, &m_RendererId);
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
        glBufferData(GL_ARRAY_BUFFER, (S32)(count * sizeof(U32)), indices, GL_STATIC_DRAW);
    }
    ~IndexBuffer()
    {
        if (m_RendererId != 0)
        {
            glDeleteBuffers(1, &m_RendererId);
        }
    }

    void Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
    }

    void Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    U32 GetCount() const
    {
        return m_Count;
    }

    static Ref<IndexBuffer> Create(U32* indices, U32 count)
    {
        return CreateRef<IndexBuffer>(indices, count);
    }

private:
    U32 m_RendererId;
    U32 m_Count;
};