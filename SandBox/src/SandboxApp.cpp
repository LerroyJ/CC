#include <CEngine.h>
#include "imgui/imgui.h"
#include<CEngine/Core/EntryPoint.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include "Sandbox2D.h"
class ExampleLayer : public CEngine::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.f/720.f)
	{
		// example quad
		shaderLibrary.Load("quadShader", "assets/shaders/test.vs", "assets/shaders/test.frag");
		m_Texture = CEngine::Texture2D::Create("assets/textures/floor.jpg");
		m_ChernoLogo = CEngine::Texture2D::Create("assets/textures/ChernoLogo.png");
		{
			float quadVertices[] = {
				// positions        // normal         //coords    //color
				-0.5f,  0.5,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.2f, 0.1f, 0.7f,
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.7f, 0.1f, 0.0f,
				 0.5,   0.5,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.6f, 0.0f,
				 0.5,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.3f, 0.0f, 0.5f
			};
			uint32_t quadIndices[] = {
					0,1,3,
					0,3,2
			};
			CEngine::Ref<CEngine::VertexBuffer> m_VertexBuffer;
			m_VertexBuffer = CEngine::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
			CEngine::Ref<CEngine::IndexBuffer> m_IndexBuffer;
			m_IndexBuffer = CEngine::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));

			CEngine::BufferLayout layout = {
				{"Position", CEngine::ShaderDataType::Float3},
				{"Normal",CEngine::ShaderDataType::Float3},
				{"TexCoord", CEngine::ShaderDataType::Float2},
				{"Color", CEngine::ShaderDataType::Float3}
			};
			m_VertexBuffer->SetLayout(layout);
			m_QuadVertexArray = CEngine::VertexArray::Create();
			m_QuadVertexArray->AddVertexBuffer(m_VertexBuffer);
			m_QuadVertexArray->SetIndexBuffer(m_IndexBuffer);
			m_QuadVertexArray->Unbind();
			m_QuadModel = glm::translate(m_QuadModel, glm::vec3(1, 0, 0));
		}
		{
			float triangleVertices[] = {
				// positions        // normal           //coords    //color
				 0.0f,   0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.2f, 0.1f, 0.7f,
				-0.75f, -0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.7f, 0.1f, 0.0f,
				 0.75f, -0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.3f, 0.0f, 0.5f
			};
			uint32_t triangleIndices[] = {
					0,1,2
			};
			CEngine::Ref<CEngine::VertexBuffer> m_VertexBuffer;
			m_VertexBuffer = CEngine::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));
			CEngine::Ref<CEngine::IndexBuffer> m_IndexBuffer;
			m_IndexBuffer = CEngine::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t));
			CEngine::BufferLayout layout = {
				{"Position", CEngine::ShaderDataType::Float3},
				{"Normal",CEngine::ShaderDataType::Float3},
				{"TexCoord", CEngine::ShaderDataType::Float2},
				{"Color", CEngine::ShaderDataType::Float3}
			};
			m_VertexBuffer->SetLayout(layout);
			m_TriangleVertexArray = CEngine::VertexArray::Create();
			m_TriangleVertexArray->AddVertexBuffer(m_VertexBuffer);
			m_TriangleVertexArray->SetIndexBuffer(m_IndexBuffer);
			m_TriangleVertexArray->Unbind();
			m_TriangleModel = glm::translate(m_TriangleModel, glm::vec3(-1, 0, 0));
		}
	}
	virtual void OnUpdate(CEngine::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);
		CEngine::RenderCommand::SetClearColor(glm::vec4(0.1, 0.2, 0.3, 1.0));
		CEngine::RenderCommand::Clear();
		auto quadShader = shaderLibrary.Get("quadShader");
		quadShader->Bind();
		std::dynamic_pointer_cast<CEngine::OpenGLShader>(quadShader)->setVec3("u_Color", m_Color);
		std::dynamic_pointer_cast<CEngine::OpenGLShader>(quadShader)->setFloat("u_Intense", m_Intense);
		
		
		CEngine::Renderer::BeginScene(m_CameraController.GetCamera());
		m_Texture->Bind();
		CEngine::Renderer::Submit(quadShader, m_QuadVertexArray);

		m_ChernoLogo->Bind();
		CEngine::Renderer::Submit(quadShader, m_QuadVertexArray);
		CEngine::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Color settings");
		ImGui::ColorEdit3("Squard Color", glm::value_ptr(m_Color));
		ImGui::SliderFloat("Intense", &m_Intense, 0.0f, 1.0f);
		ImGui::End();
	}

	virtual void OnEvent(CEngine::Event& event) override {
		m_CameraController.OnEvent(event);
	}
private:
	// model
	CEngine::Ref<CEngine::VertexArray> m_QuadVertexArray;
	CEngine::Ref<CEngine::VertexArray> m_TriangleVertexArray;
	glm::mat4 m_QuadModel = glm::mat4(1);
	glm::mat4 m_TriangleModel = glm::mat4(1);

	// shader
	CEngine::ShaderLibrary shaderLibrary;
	glm::vec3 m_Color = {0.1f, 0.8f, 0.1f};
	float m_Intense = 0.0f;

	// camera
	CEngine::OrthographicCameraController m_CameraController;

	// texture
	CEngine::Ref<CEngine::Texture2D> m_Texture;
	CEngine::Ref<CEngine::Texture2D> m_ChernoLogo;
};

class Sandbox : public CEngine::Application {
public:
	Sandbox() {
		PushLayer(new Sandbox2D());
		//PushLayer(new ExampleLayer());
	}
	~Sandbox() {}
};

CEngine::Application* CEngine::CreateApplication() {
	return new Sandbox();
}