#include "avpch.h"
#include "Avalon/Renderer/GraphicsContext.h"

#include "Avalon/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Avalon {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    AV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		AV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}