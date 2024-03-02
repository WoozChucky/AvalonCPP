#include "avpch.h"
#include "Buffer.h"

#include "Avalon/Core/Base.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Avalon
{
	Ref<VertexBuffer> VertexBuffer::Create(U32 size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    AV_CORE_ASSERT(false, "Renderer"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(size);
		}

		AV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(F32* vertices, U32 size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    AV_CORE_ASSERT(false, "Renderer"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		AV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(U32* indices, U32 count)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    AV_CORE_ASSERT(false, "Renderer"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		AV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}