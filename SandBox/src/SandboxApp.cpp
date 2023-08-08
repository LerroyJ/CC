#include <CEngine.h>
#include "imgui/imgui.h"
class ExampleLayer : public CEngine::Layer {
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(m_Camera.GetPosition())
	{
		// example quad
		m_Shader.reset(CEngine::Shader::Create("D:/Users/DELL/source/repos/CEngine/CEngine/shader/test.vs", "D:/Users/DELL/source/repos/CEngine/CEngine/shader/test.frag"));

		{
			float quadVertices[] = {
				// positions        // normal               //coords    //color
				-0.5f,  0.5,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.2f, 0.1f, 0.7f,
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.7f, 0.1f, 0.0f,
				 0.5,   0.5,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.6f, 0.0f,
				 0.5,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.3f, 0.0f, 0.5f
			};
			uint32_t quadIndices[] = {
					0,1,3,
					0,3,2
			};
			std::shared_ptr<CEngine::VertexBuffer> m_VertexBuffer;
			m_VertexBuffer.reset(CEngine::VertexBuffer::Create(quadVertices, sizeof(quadVertices)));
			std::shared_ptr<CEngine::IndexBuffer> m_IndexBuffer;
			m_IndexBuffer.reset(CEngine::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t)));

			CEngine::BufferLayout layout = {
				{"Position", CEngine::ShaderDataType::Float3},
				{"Normal",CEngine::ShaderDataType::Float3},
				{"TexCoord", CEngine::ShaderDataType::Float2},
				{"Color", CEngine::ShaderDataType::Float3}
			};
			m_VertexBuffer->SetLayout(layout);
			m_QuadVertexArray.reset(CEngine::VertexArray::Create());
			m_QuadVertexArray->AddVertexBuffer(m_VertexBuffer);
			m_QuadVertexArray->SetIndexBuffer(m_IndexBuffer);
			m_QuadVertexArray->Unbind();
			m_QuadModel = glm::translate(m_QuadModel, glm::vec3(1, 0, 0));
		}
		{
			float triangleVertices[] = {
				// positions        // normal               //coords    //color
				 0.0f,   0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.2f, 0.1f, 0.7f,
				-0.75f, -0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.7f, 0.1f, 0.0f,
				 0.75f, -0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.3f, 0.0f, 0.5f
			};
			uint32_t triangleIndices[] = {
					0,1,2
			};
			std::shared_ptr<CEngine::VertexBuffer> m_VertexBuffer;
			m_VertexBuffer.reset(CEngine::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
			std::shared_ptr<CEngine::IndexBuffer> m_IndexBuffer;
			m_IndexBuffer.reset(CEngine::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
			CEngine::BufferLayout layout = {
				{"Position", CEngine::ShaderDataType::Float3},
				{"Normal",CEngine::ShaderDataType::Float3},
				{"TexCoord", CEngine::ShaderDataType::Float2},
				{"Color", CEngine::ShaderDataType::Float3}
			};
			m_VertexBuffer->SetLayout(layout);
			m_TriangleVertexArray.reset(CEngine::VertexArray::Create());
			m_TriangleVertexArray->AddVertexBuffer(m_VertexBuffer);
			m_TriangleVertexArray->SetIndexBuffer(m_IndexBuffer);
			m_TriangleVertexArray->Unbind();
			m_TriangleModel = glm::translate(m_TriangleModel, glm::vec3(-1, 0, 0));
		}
	}
	virtual void OnUpdate(CEngine::Timestep ts) override
	{
		if (CEngine::Input::IsKeyPressed(CC_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (CEngine::Input::IsKeyPressed(CC_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}
		if (CEngine::Input::IsKeyPressed(CC_KEY_UP)) {
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}
		else if (CEngine::Input::IsKeyPressed(CC_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		if (CEngine::Input::IsKeyPressed(CC_KEY_A)) {
			m_CameraRotation += m_CameraRotationSpeed * ts.GetSecond();
		}
		else if (CEngine::Input::IsKeyPressed(CC_KEY_D)) {
			m_CameraRotation -= m_CameraRotationSpeed * ts.GetSecond();
		}
		CEngine::RenderCommand::SetClearColor(glm::vec4(0.1, 0.2, 0.3, 1.0));
		CEngine::RenderCommand::Clear();

		m_Camera.SetRotation(m_CameraRotation);
		m_Camera.SetPosition(m_CameraPosition);
		CEngine::Renderer::BeginScene(m_Camera);
		CEngine::Renderer::Submit(m_Shader, m_QuadVertexArray, m_QuadModel);
		CEngine::Renderer::Submit(m_Shader, m_TriangleVertexArray);
		CEngine::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
	}

	virtual void OnEvent(CEngine::Event& event) override {
		CEngine::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<CEngine::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(CEngine::KeyPressedEvent event) {
		return false;
	}
private:
	std::shared_ptr<CEngine::VertexArray> m_QuadVertexArray;
	glm::mat4 m_QuadModel = glm::mat4(1);
	std::shared_ptr<CEngine::VertexArray> m_TriangleVertexArray;
	glm::mat4 m_TriangleModel = glm::mat4(1);

	std::shared_ptr<CEngine::Shader> m_Shader;
	CEngine::OrthograhpicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 12.f;
};

class Sandbox : public CEngine::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}
};

CEngine::Application* CEngine::CreateApplication() {
	return new Sandbox();
}