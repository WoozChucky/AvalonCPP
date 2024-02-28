#include "avpch.h"
#include "Application.h"

#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Avalon
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		AV_TRACE(e);

		while (true);
	}
}