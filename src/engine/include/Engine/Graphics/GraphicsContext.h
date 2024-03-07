#pragma once

#include <Common/Types.h>
#include <Common/Logging/Log.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Avalon::Engine
{
    class GraphicsContext
    {
    public:
        GraphicsContext(GLFWwindow* window)
            : m_Window(window) {}

        void Init() {
            glfwMakeContextCurrent(m_Window);
            int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            if (!status)
            {
                LOG_ERROR("GLAD", "Failed to initialize GLAD");
            }
            auto vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
            auto renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
            auto version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
            LOG_INFO("OpenGL", "Vendor: {}", vendor);
            LOG_INFO("OpenGL", "Renderer: {}", renderer);
            LOG_INFO("OpenGL", "Version: {}", version);
        }
        void SwapBuffers() { glfwSwapBuffers(m_Window); }

    public:
        static Scope<GraphicsContext> Create(GLFWwindow* window) { return CreateScope<GraphicsContext>(window); }
    private:
        GLFWwindow* m_Window;
    };
}