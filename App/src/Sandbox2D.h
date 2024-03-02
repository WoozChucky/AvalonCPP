#pragma once

#include "Avalon.h"

#include "ParticleSystem.h"

#include <vector>

class Sandbox2D : public Avalon::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Avalon::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Avalon::Event& e) override;

private:
	Avalon::OrthographicCameraController m_CameraController;

	// Temp
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	Avalon::Ref<Avalon::Texture2D> m_CheckerboardTexture;

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;

};