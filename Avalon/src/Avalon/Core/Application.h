#pragma once

#include "Avalon/Core/Base.h"
#include "Avalon/Core/Timestep.h"

#include "Avalon/Core/Window.h"

#include "Avalon/Core/LayerStack.h"

#include "Avalon/Events/Event.h"
#include "Avalon/Events/ApplicationEvent.h"

#include "Avalon/ImGui/ImGuiLayer.h"

namespace Avalon
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Close();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		static Application* s_Instance;

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		F32 m_LastFrameTime = 0.0f;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


