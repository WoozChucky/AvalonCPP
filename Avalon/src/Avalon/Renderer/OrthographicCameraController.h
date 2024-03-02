#pragma once

#include "Avalon/Core/Base.h"
#include "Avalon/Renderer/OrthographicCamera.h"
#include "Avalon/Core/Timestep.h"

#include "Avalon/Events/ApplicationEvent.h"
#include "Avalon/Events/MouseEvent.h"


namespace Avalon
{
	struct OrthographicCameraBounds
	{
		F32 Left, Right;
		F32 Bottom, Top;

		F32 GetWidth() { return Right - Left; }
		F32 GetHeight() { return Top - Bottom; }
	};

	// TODO: Add support for gamepad/controller input
	/// <summary>
	/// A controller for an orthographic camera - 2D camera controller
	/// </summary>
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(F32 aspectRatio, bool rotation = false);

		void OnUpdate(Timestep deltaTime);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		F32 GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(F32 level) { m_ZoomLevel = level; CalculateView(); }

		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

	private:
		void CalculateView();

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		F32 m_AspectRatio;
		F32 m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		OrthographicCameraBounds m_Bounds;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		F32 m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
		F32 m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
	};
}