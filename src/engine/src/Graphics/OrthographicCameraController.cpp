#include <Engine/Graphics/OrthographicCameraController.h>

#include <Engine/Core/Input.h>
#include <Engine/Core/KeyCodes.h>

namespace Avalon
{
    OrthographicCameraController::OrthographicCameraController(F32 aspectRatio, bool rotation)
            : m_AspectRatio(aspectRatio),
              m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
              m_Rotation(rotation),
              m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel })
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        if (Input::IsKeyPressed(Avalon::Key::A))
            m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(Avalon::Key::D))
            m_CameraPosition.x += m_CameraTranslationSpeed * ts;

        if (Input::IsKeyPressed(Avalon::Key::W))
            m_CameraPosition.y += m_CameraTranslationSpeed * ts;
        else if (Input::IsKeyPressed(Avalon::Key::S))
            m_CameraPosition.y -= m_CameraTranslationSpeed * ts;

        if (m_Rotation)
        {
            if (Input::IsKeyPressed(Avalon::Key::Q))
                m_CameraRotation += m_CameraRotationSpeed * ts;
            if (Input::IsKeyPressed(Avalon::Key::E))
                m_CameraRotation -= m_CameraRotationSpeed * ts;

            m_Camera.SetRotation(m_CameraRotation);
        }

        m_Camera.SetPosition(m_CameraPosition);

        m_CameraTranslationSpeed = m_ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }

    void OrthographicCameraController::CalculateView()
    {
        m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel };
        m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel -= e.GetYOffset() * 0.25f;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        CalculateView();
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
    {
        m_AspectRatio = (F32)e.GetWidth() / (F32)e.GetHeight();
        CalculateView();
        return false;
    }
}