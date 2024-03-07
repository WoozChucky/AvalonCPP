#pragma once

#include <Engine/Core/Application.h>
#include <Engine/Graphics/Renderers/RendererAPI.h>
#include <Engine/Graphics/Renderers/Renderer2D.h>
#include <Engine/Graphics/Raw/Texture2D.h>
#include <Engine/Graphics/OrthographicCameraController.h>

class TestLayer : public Avalon::Layer
{
public:
    TestLayer() : Layer("Test"), m_Camera(16.0f / 9.0f) {}
    void OnAttach() override {
        m_Texture = Avalon::Texture2D::Create("assets/textures/icon.png");
    }
    void OnEvent(Avalon::Event& event) override {

    }
    void OnUpdate(Avalon::Timestep ts) override {

        Avalon::RendererAPI::SetClearColor({ 0.25f, 0.25f, 0.25f, 0.85f });
        Avalon::RendererAPI::Clear();

        Avalon::Renderer2D::BeginScene(m_Camera.GetCamera());
        Avalon::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Texture);
        Avalon::Renderer2D::EndScene();

    }
    void OnImGuiRender() override {

    }

private:
    Avalon::OrthographicCameraController m_Camera;
    Ref<Avalon::Texture2D> m_Texture;
};

class AvalonGame : public Avalon::Application
{
public:
    AvalonGame(const Avalon::ApplicationSpecification& specification) : Avalon::Application(specification) {
        PushLayer(new TestLayer());
    }
    ~AvalonGame() {}
};