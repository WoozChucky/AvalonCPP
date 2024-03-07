#include <Engine/Core/Window.h>
#include <Engine/Events/ApplicationEvent.h>
#include <Engine/Events/KeyEvent.h>
#include <Engine/Events/MouseEvent.h>
#include <Common/Logging/Log.h>


namespace Avalon::Engine
{
    static U8 s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description)
    {
        LOG_ERROR("GLFW", "Error ({}): {}", error, description);
    }

    Window::Window(const GameSettings &settings) {
        Init(settings);
    }

    Window::~Window() {
        Shutdown();
    }

    void Window::Init(const GameSettings &settings) {
        m_Settings = settings;

        m_Data.Width = settings.Video.Resolution.Width;
        m_Data.Height = settings.Video.Resolution.Height;

        if (s_GLFWWindowCount == 0)
        {
            auto success = glfwInit();
            if (!success)
            {
                LOG_ERROR("GLFW", "Failed to initialize GLFW");
                return;
            }

            glfwSetErrorCallback(GLFWErrorCallback);
        }


#if defined(AV_DEBUG)
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

        m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, u8"AABB", nullptr, nullptr);

        ++s_GLFWWindowCount;

        m_Context = GraphicsContext::Create(m_Window);
        m_Context->Init();

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        SetupCallbacks();

    }

    void Window::SetVSync(bool enabled) {
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
        m_Data.VSync = enabled;
    }

    bool Window::IsVSync() const {
        return m_Data.VSync;
    }

    void Window::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void Window::OnUpdate()
    {
        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void Window::SetupCallbacks() {

        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
          {
              WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
              data.Width = width;
              data.Height = height;

              WindowResizeEvent event(width, height);
              data.EventCallback(event);
          }
        );

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
           {
               WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
               WindowCloseEvent event;
               data.EventCallback(event);
           }
        );

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
           {
               WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

               switch (action)
               {
                   case GLFW_PRESS:
                   {
                       KeyPressedEvent event(static_cast<KeyCode>(key), 0);
                       data.EventCallback(event);
                       break;
                   }
                   case GLFW_RELEASE:
                   {
                       KeyReleasedEvent event(static_cast<KeyCode>(key));
                       data.EventCallback(event);
                       break;
                   }
                   case GLFW_REPEAT:
                   {
                       KeyPressedEvent event(static_cast<KeyCode>(key), 1);
                       data.EventCallback(event);
                       break;
                   }
               }
           }
        );

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                KeyTypedEvent event(static_cast<KeyCode>(keycode));
                data.EventCallback(event);
            }
        );

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
           {
               WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

               switch (action)
               {
                   case GLFW_PRESS:
                   {
                       MouseButtonPressedEvent event(static_cast<MouseCode>(button));
                       data.EventCallback(event);
                       break;
                   }
                   case GLFW_RELEASE:
                   {
                       MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
                       data.EventCallback(event);
                       break;
                   }
               }
           }
        );

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
          {
              WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
              MouseScrolledEvent event((F32)xOffset, (F32)yOffset);
              data.EventCallback(event);
          }
        );

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
             {
                 WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                 MouseMovedEvent event((F32)xPos, (F32)yPos);
                 data.EventCallback(event);
             }
        );

        glfwSetWindowRefreshCallback(m_Window, [](GLFWwindow* window)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                WindowResizeEvent event(data.Width, data.Height);
                data.EventCallback(event);
            }
        );
    }
}



