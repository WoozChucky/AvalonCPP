#pragma once

#include "Avalon/Core/Base.h"
#include "Avalon/Events/Event.h"

namespace Avalon
{
	struct WindowProps
	{
		std::string Title;
		U32 Width;
		U32 Height;

		WindowProps(const std::string& title = "Avalon Engine",
						U32 width = 1280,
						U32 height = 720)
			: Title(title), Width(width), Height(height) 
		{
		}
	};

	// Interface representing a desktop system based Window
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual U32 GetWidth() const = 0;
		virtual U32 GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}