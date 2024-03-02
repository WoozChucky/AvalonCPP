#pragma once

#include "Avalon/Core/Base.h"

#include <glm/glm.hpp>

namespace Avalon
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(F32 left, F32 right, F32 bottom, F32 top);

		void SetProjection(F32 left, F32 right, F32 bottom, F32 top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		F32 GetRotation() const { return m_Rotation; }
		void SetRotation(F32 rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		F32 m_Rotation = 0.0f;
	};
}