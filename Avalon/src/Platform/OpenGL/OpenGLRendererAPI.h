#pragma once

#include "Avalon/Renderer/RendererAPI.h"

namespace Avalon
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void SetViewport(U32 x, U32 y, U32 width, U32 height) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, U32 indexCount = 0) override;
	};
}