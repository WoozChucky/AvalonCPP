#pragma once

#include "Avalon.h"

class RPGLayer : public Avalon::Layer
{
public:
	RPGLayer();
	virtual ~RPGLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Avalon::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Avalon::Event& e) override;

private:
	Avalon::OrthographicCameraController m_CameraController;

	Avalon::Ref<Avalon::Texture2D> m_SpriteSheet;
	Avalon::Ref<Avalon::SubTexture2D> m_TextureStairs;
	Avalon::Ref<Avalon::SubTexture2D> m_TextureBarrel;
};