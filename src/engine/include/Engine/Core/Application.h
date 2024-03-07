#pragma once

#include <Engine/Events/ApplicationEvent.h>
#include <Engine/Core/Window.h>
#include <Engine/Core/LayerStack.h>
#include <Engine/ImGui/ImGuiLayer.h>

namespace Avalon
{
    struct ApplicationCommandLineArgs
    {
        S32 Count = 0;
        char** Args = nullptr;

        const char* operator[](S32 index) const
        {
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

        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        void Run();
        void Close();

        void SubmitToMainThread(const std::function<void()>& function);

    public:
        static Application& Get() { return *s_Instance; }
        Engine::Window& GetWindow() { return *m_Window; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

        void ExecuteMainThreadQueue();

    private:
        ApplicationSpecification m_Specification;
        Scope<Engine::Window> m_Window;
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

    Application* CreateApplication(ApplicationCommandLineArgs args);
}