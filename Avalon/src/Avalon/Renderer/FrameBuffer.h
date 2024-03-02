#pragma once

#include "Avalon/Core/Base.h"

namespace Avalon
{
	struct FrameBufferSpecification
	{
		U32 Width, Height;
		U32 Samples = 1;

		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(U32 width, U32 height) = 0;

		virtual U32 GetColorAttachmentRendererID() const = 0;
		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);

	private:
		FrameBufferSpecification m_Specification;
	};
}