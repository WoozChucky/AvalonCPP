#include "avpch.h"

#include "OpenGLUniformBuffer.h"

#include <glad/glad.h>

namespace Avalon
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(U32 size, U32 binding)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLUniformBuffer::SetData(const void* data, U32 size, U32 offset)
	{
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}
}