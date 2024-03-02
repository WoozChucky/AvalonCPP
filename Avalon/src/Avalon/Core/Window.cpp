#include "avpch.h"
#include "Avalon/Core/Window.h"

#ifdef AV_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Avalon
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef AV_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		AV_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}