#pragma once

#include "Avalon/Core/Window.h"
#include "Avalon/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace Avalon {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline U32 GetWidth() const override { return m_Data.Width; }
		inline U32 GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetNativeWindow() const override { return m_Window; }
	
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string Title;
			U32 Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		} m_Data;
	};

}