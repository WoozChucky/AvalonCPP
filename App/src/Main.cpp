#include <Avalon.h>
#include <Avalon/Core/EntryPoint.h>

#include <imgui/imgui.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"
#include "RPGLayer.h"

class ExampleLayer : public Avalon::Layer
{
public:
	ExampleLayer()
		: Layer("Example"),
		m_Camera(1280.f / 720.f, true)
	{


		m_VertexArray = Avalon::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};

		Avalon::Ref<Avalon::VertexBuffer> verterBuffer(Avalon::VertexBuffer::Create(vertices, sizeof(vertices)));


		verterBuffer->SetLayout({
			{ Avalon::ShaderDataType::Float3, "a_Position" },
			{ Avalon::ShaderDataType::Float4, "a_Color" }
			});
		m_VertexArray->AddVertexBuffer(verterBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		Avalon::Ref<Avalon::IndexBuffer> indexBuffer(Avalon::IndexBuffer::Create(indices, std::size(indices)));

		m_VertexArray->SetIndexBuffer(indexBuffer);
		m_VertexArray->Unbind();


		// Square

		m_SquareVA = Avalon::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Avalon::Ref<Avalon::VertexBuffer> squareVB;
		squareVB = Avalon::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Avalon::ShaderDataType::Float3, "a_Position" },
			{ Avalon::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Avalon::Ref<Avalon::IndexBuffer> squareIB;
		squareIB = Avalon::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 410 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 410 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		std::string flatColorShaderVertexSrc = R"(
			#version 410 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 410 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		std::string textureShaderVertexSrc = R"(
			#version 410 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				v_TexCoord = a_TexCoord;
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 410 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;
			
			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_FlatColorShader = Avalon::Shader::Create("FlatColorShader", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		
		m_Shader =  Avalon::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");
		
		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);

		m_Texture = Avalon::Texture2D::Create("Assets/Textures/icon.png");
	}

	void OnUpdate(Avalon::Timestep ts) override
	{
		// AV_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());


		if (Avalon::Input::IsKeyPressed(Avalon::Key::W))
		{
			m_TrianglePosition.y += m_TriangleSpeed * ts;
		}
		else if (Avalon::Input::IsKeyPressed(Avalon::Key::S))
		{
			m_TrianglePosition.y -= m_TriangleSpeed * ts;
		}

		if (Avalon::Input::IsKeyPressed(Avalon::Key::A))
		{
			m_TrianglePosition.x -= m_TriangleSpeed * ts;
		}
		else if (Avalon::Input::IsKeyPressed(Avalon::Key::D))
		{
			m_TrianglePosition.x += m_TriangleSpeed * ts;
		}

		m_Camera.OnUpdate(ts);

		Avalon::RenderCommand::Clear();
		Avalon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });


		Avalon::Renderer::BeginScene(m_Camera.GetCamera());
		{

			//glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_TrianglePosition);

			//Avalon::Renderer::Submit(m_Shader, m_SquareVA);
			//Avalon::Renderer::Submit(m_Shader, m_VertexArray, transform);

			static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

			m_FlatColorShader->Bind();
			m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);
			
			for (int y = 0; y < 20; y++)
			{
				for (int x = 0; x < 20; x++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Avalon::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
				}
			}

			m_Texture->Bind();
			Avalon::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

			//Avalon::Renderer::Submit(m_Shader, m_VertexArray);

		}
		Avalon::Renderer::EndScene();
		
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::ColorEdit3("Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Avalon::Event& event) override
	{
		// AV_TRACE("{0}", event);
		m_Camera.OnEvent(event);

		if (event.GetEventType() == Avalon::EventType::WindowResize)
		{
			//auto& e = (Avalon::WindowResizeEvent&)event;
			//m_Camera.SetZoomLevel((F32)e.GetWidth() / (F32)e.GetHeight());
		}
	}

private:
	Avalon::ShaderLibrary m_ShaderLibrary;
	Avalon::Ref<Avalon::Shader> m_FlatColorShader;
	Avalon::Ref<Avalon::Shader> m_Shader;
	Avalon::Ref<Avalon::VertexArray> m_VertexArray;
	Avalon::Ref<Avalon::VertexArray> m_SquareVA;
	Avalon::Ref<Avalon::Texture2D> m_Texture;

	Avalon::OrthographicCameraController m_Camera;

	F32 m_TriangleSpeed = 1.0f;
	glm::vec3 m_TrianglePosition = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class AvalonApplication : public Avalon::Application
{
public:
	AvalonApplication()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
		//PushLayer(new RPGLayer());
	}

	~AvalonApplication()
	{
	}

};

Avalon::Application* Avalon::CreateApplication()
{
	return new AvalonApplication();
}

