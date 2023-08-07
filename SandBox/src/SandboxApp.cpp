#include <CEngine.h>
#include "imgui/imgui.h"

class ExampleLayer : public CEngine::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{
		// example quad
		m_Shader.reset(CEngine::Shader::Create("D:/Users/DELL/source/repos/CEngine/CEngine/shader/test.vs", "D:/Users/DELL/source/repos/CEngine/CEngine/shader/test.frag"));

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
		m_VertexArray.reset(CEngine::VertexArray::Create());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	}
	virtual void OnUpdate() override
	{
		if (CEngine::Input::IsKeyPressed(CC_KEY_A)) {
			CC_CORE_TRACE("A is pressed!");
		}
		CEngine::RenderCommand::SetClearColor(glm::vec4(0.1, 0.2, 0.3, 1.0));
		CEngine::RenderCommand::Clear();

		m_Shader->Bind();
		CEngine::Renderer::BeginScene();
		CEngine::Renderer::Submit(m_VertexArray);
		CEngine::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
	}

	virtual void OnEvent(CEngine::Event& event) override {
		if (CEngine::EventType::KeyPressed == event.GetEventType()) {
			CC_TRACE((char)((CEngine::KeyPressedEvent&)event).GetKeyCode());
		}
	}
private:
	std::shared_ptr<CEngine::VertexArray> m_VertexArray;
	std::shared_ptr<CEngine::Shader> m_Shader;
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