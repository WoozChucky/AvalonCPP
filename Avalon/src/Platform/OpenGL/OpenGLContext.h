#pragma once

#include "Avalon/Renderer/GraphicsContext.h"

struct GLFWwindow; // Forward declaration

namespace Avalon
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}