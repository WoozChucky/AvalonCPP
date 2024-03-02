#include "avpch.h"

#include "OpenGLContext.h"

#include "Avalon/Core/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Avalon 
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		AV_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		AV_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AV_CORE_ASSERT(status, "Failed to initialize Glad!");

		auto vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		auto renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		auto version = reinterpret_cast<const char*>(glGetString(GL_VERSION));

		AV_CORE_INFO("OpenGL Info:");
		AV_CORE_INFO("  Vendor: {0}", vendor);
		AV_CORE_INFO("  Renderer: {0}", renderer);
		AV_CORE_INFO("  Version: {0}", version);
	}

	void OpenGLContext::SwapBuffers()
	{
		AV_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}