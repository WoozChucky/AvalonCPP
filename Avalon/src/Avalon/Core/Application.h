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

	struct ApplicationCommandLineArgs
	{
		S32 Count = 0;
		char** Args = nullptr;

		const char* operator[](S32 index) const
		{
			AV_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "Avalon";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};


	class Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }

		const ApplicationSpecification& GetSpecification() const { return m_Specification; }

		void SubmitToMainThread(const std::function<void()>& function);

		void Run();
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		void ExecuteMainThreadQueue();
	private:
		ApplicationSpecification m_Specification;
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		F32 m_LastFrameTime = 0.0f;

		std::vector<std::function<void()>> m_MainThreadQueue;
		std::mutex m_MainThreadQueueMutex;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication(ApplicationCommandLineArgs args);
}


