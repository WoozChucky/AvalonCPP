#include "avpch.h"

#include "Texture.h"

#include "Avalon/Core/Log.h"


#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Avalon 
{
	Ref<Texture2D> Texture2D::Create(U32 width, U32 height)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    AV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(width, height);
		}

		AV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    AV_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		}

		AV_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}