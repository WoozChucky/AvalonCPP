#include "avpch.h"
#include "Avalon/Renderer/UniformBuffer.h"

#include "Avalon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Avalon
{
	Ref<UniformBuffer> UniformBuffer::Create(U32 size, U32 binding)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    AV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		AV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}