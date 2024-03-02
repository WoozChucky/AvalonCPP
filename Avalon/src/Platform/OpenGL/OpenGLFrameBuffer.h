#pragma once

#include "Avalon/Renderer/FrameBuffer.h"

namespace Avalon
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(U32 width, U32 height) override;

		virtual U32 GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		U32 m_RendererID = 0;
		U32 m_ColorAttachment = 0, m_DepthAttachment = 0;
		FrameBufferSpecification m_Specification;
	};
}