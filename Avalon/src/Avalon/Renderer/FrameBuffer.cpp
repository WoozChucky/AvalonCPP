#include "avpch.h"

#include "Avalon/Renderer/FrameBuffer.h"
#include "Avalon/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Avalon {
	
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    AV_CORE_ASSERT(false, "Renderer");
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFrameBuffer>(spec);
		}

		AV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}