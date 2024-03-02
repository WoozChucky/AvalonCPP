#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
	AV_PROFILE_FUNCTION();

	m_Particle.ColorBegin = { 0.8f, 0.3f, 0.2f, 1.0f };
	m_Particle.ColorEnd = { 0.2f, 0.3f, 0.8f, 1.0f };
	
	m_Particle.SizeBegin = 0.5f;
	m_Particle.SizeVariation = 0.3f;
	m_Particle.SizeEnd = 0.0f;
	
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
	
	m_Particle.LifeTime = 1.0f;

	m_ParticleSystem = ParticleSystem();
}

void Sandbox2D::OnAttach()
{
	AV_PROFILE_FUNCTION();

	m_CheckerboardTexture = Avalon::Texture2D::Create("assets/textures/Checkboard.png");
}

void Sandbox2D::OnDetach()
{
	AV_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Avalon::Timestep ts)
{
	AV_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	if (Avalon::Input::IsMouseButtonPressed(AV_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Avalon::Input::GetMousePosition();
		auto width = Avalon::Application::Get().GetWindow().GetWidth();
		auto height = Avalon::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();

		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 2; i++)
			m_ParticleSystem.Emit(m_Particle);
	}
	
	m_ParticleSystem.OnUpdate(ts);
	
	// Render
	Avalon::Renderer2D::ResetStats();
	{
		AV_PROFILE_SCOPE("Renderer Prep");
		Avalon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Avalon::RenderCommand::Clear();
	}
	
	{
		AV_PROFILE_SCOPE("Renderer Draw");

		static F32 rotation = 0.0f;
		rotation += ts * 50.0f;

		Avalon::Renderer2D::BeginScene(m_CameraController.GetCamera());
		{
			Avalon::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
			Avalon::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
			Avalon::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
			Avalon::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
			Avalon::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
			Avalon::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerboardTexture, 10.0f);

			for (F32 y = -5.0f; y < 5.0f; y += 0.5f)
			{
				for (F32 x = -5.0f; x < 5.0f; x += 0.5f)
				{
					glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 1.0f };
					Avalon::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
				}
			}
		
		}
		Avalon::Renderer2D::EndScene();
	}

	m_ParticleSystem.OnRender(m_CameraController.GetCamera());
	
}

void Sandbox2D::OnImGuiRender()
{
	AV_PROFILE_FUNCTION();
	ImGui::Begin("Settings");

	auto stats = Avalon::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());


	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Avalon::Event& e)
{
	m_CameraController.OnEvent(e);
}