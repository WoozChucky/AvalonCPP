#pragma once

#include <Common/Types.h>
#include <glad/glad.h>

namespace Avalon
{
    class UniformBuffer
    {
    public:
        UniformBuffer(U32 size, U32 binding) {
            glGenBuffers(1, &m_RendererId);
            glBindBuffer(GL_UNIFORM_BUFFER, m_RendererId);
            glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
            glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererId);
        }
        virtual ~UniformBuffer() {
            glDeleteBuffers(1, &m_RendererId);
        }

        virtual void SetData(const void* data, U32 size, U32 offset = 0) {
            glBindBuffer(GL_UNIFORM_BUFFER, m_RendererId);
            glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
        }

        static Ref<UniformBuffer> Create(U32 size, U32 binding) {
            return CreateRef<UniformBuffer>(size, binding);
        }
    private:
        U32 m_RendererId;
    };
}