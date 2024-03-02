#include "avpch.h"

#include "Avalon/Core/Input.h"

#ifdef AV_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif

namespace Avalon {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
	#ifdef AV_PLATFORM_WINDOWS
			return CreateScope<WindowsInput>();
	#else
			AV_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
	#endif
	}
}