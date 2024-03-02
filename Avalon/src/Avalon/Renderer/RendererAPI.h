#pragma once

#include "Avalon/Core/Base.h"
#include "Avalon/Renderer/VertexArray.h"

#include <glm/glm.hpp>


namespace Avalon
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

		virtual void Init() = 0;
		virtual void SetViewport(U32 x, U32 y, U32 width, U32 height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, U32 indexCount = 0) = 0;

		inline static API GetAPI() { return s_API; }
		static Scope<RendererAPI> Create();
	private:
		static API s_API;
	};
}