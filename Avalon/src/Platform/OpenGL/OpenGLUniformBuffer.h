#pragma once

#include "Avalon/Renderer/UniformBuffer.h"

namespace Avalon
{

	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(U32 size, U32 binding);
		virtual ~OpenGLUniformBuffer();

		virtual void SetData(const void* data, U32 size, U32 offset = 0) override;


	private:
		U32 m_RendererID;
	};
}