#include "RPGLayer.h"

#include <imgui/imgui.h>

RPGLayer::RPGLayer()
	: Layer("RPGLayer"), m_CameraController(1280.0f / 720.0f)
{
}

void RPGLayer::OnAttach()
{
	AV_PROFILE_FUNCTION();

	m_SpriteSheet = Avalon::Texture2D::Create("assets/textures/atlas.png");
	m_TextureStairs = Avalon::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128, 128 });
	m_TextureBarrel = Avalon::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 8, 2 }, { 128, 128 });
}

void RPGLayer::OnDetach()
{
	AV_PROFILE_FUNCTION();
}

void RPGLayer::OnUpdate(Avalon::Timestep ts)
{
	AV_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Avalon::Renderer2D::ResetStats();
	{
		AV_PROFILE_SCOPE("Renderer Prep");
		Avalon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Avalon::RenderCommand::Clear();
	}
	

	Avalon::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		Avalon::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_TextureStairs);
		Avalon::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_TextureBarrel);
	}
	Avalon::Renderer2D::EndScene();
}

void RPGLayer::OnImGuiRender()
{
	AV_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	auto stats = Avalon::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();
}

void RPGLayer::OnEvent(Avalon::Event& e)
{
	m_CameraController.OnEvent(e);
}

