#pragma once

#include <Common/Types.h>
#include <Engine/Settings.h>
#include <Engine/Graphics/GraphicsContext.h>
#include <Engine/Events/Event.h>
#include <GLFW/glfw3.h>

namespace Avalon::Engine
{
    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        explicit Window(const GameSettings& settings);
        ~Window();
        void Shutdown();

        void OnUpdate();

        U32 GetWidth() const { return m_Data.Width; };
        U32 GetHeight() const { return m_Data.Height; }

        void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled);
        bool IsVSync() const;

        void* GetNativeWindow() const { return m_Window; }

    public:
        static Scope<Window> Create(const GameSettings& settings) { return CreateScope<Window>(settings); }
    private:

        void Init(const GameSettings& settings);
        void SetupCallbacks();
    private:
        Scope<GraphicsContext> m_Context;
        GLFWwindow* m_Window;
        GameSettings m_Settings;

        struct WindowData
        {
            U32 Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        } m_Data;
    };
}

