#include "avpch.h"

#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Avalon
{
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         AV_CORE_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       AV_CORE_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          AV_CORE_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: AV_CORE_TRACE(message); return;
		}

		AV_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRendererAPI::Init()
	{
		AV_PROFILE_FUNCTION();

	#ifdef AV_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
	#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
	}

	void OpenGLRendererAPI::SetViewport(U32 x, U32 y, U32 width, U32 height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, U32 indexCount)
	{
		vertexArray->Bind();
		U32 count = indexCount == 0 ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, U32 vertexCount)
	{
		vertexArray->Bind();
		glDrawElements(GL_LINES, vertexCount, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::SetLineWidth(F32 width)
	{
		glLineWidth(width);
	}
}