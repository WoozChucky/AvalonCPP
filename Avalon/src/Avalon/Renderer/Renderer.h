#pragma once

#include "Avalon/Core/Base.h"
#include "Avalon/Renderer/RenderCommand.h"
#include "Avalon/Renderer/OrthographicCamera.h"
#include "Avalon/Renderer/Shader.h"

namespace Avalon
{
	class Renderer
	{
	public:
		
		static void Init();
		static void Shutdown();

		static void OnWindowResize(U32 width, U32 height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,
			const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};
}