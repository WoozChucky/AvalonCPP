#include "avpch.h"

#include "Avalon/Renderer/RenderCommand.h"

namespace Avalon
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}