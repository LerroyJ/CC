#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
	m_QuadShader = CEngine::Shader::Create("flatShader", "assets/shaders/test.vs", "assets/shaders/test.frag");
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
	CEngine::BufferLayout layout = {
		{"Position", CEngine::ShaderDataType::Float3},
		{"Normal",CEngine::ShaderDataType::Float3},
		{"TexCoord", CEngine::ShaderDataType::Float2},
		{"Color", CEngine::ShaderDataType::Float3}
	};
	CEngine::Ref<CEngine::VertexBuffer> vertexBuffer = CEngine::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
	vertexBuffer->SetLayout(layout);
	CEngine::Ref<CEngine::IndexBuffer> indexBuffer = CEngine::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
	m_QuadVA = CEngine::VertexArray::Create();
	m_QuadVA->AddVertexBuffer(vertexBuffer);
	m_QuadVA->SetIndexBuffer(indexBuffer);
	m_QuadVA->Unbind();
}

void Sandbox2D::OnUpdate(CEngine::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
	CEngine::RenderCommand::Clear();
	CEngine::RenderCommand::SetClearColor({ 0.1, 0.2, 0.3, 1.0 });
	std::dynamic_pointer_cast<CEngine::OpenGLShader>(m_QuadShader)->setMat4("u_ViewProjectionMatrix", m_CameraController.GetCamera().GetViewProjectionMatrix());
	std::dynamic_pointer_cast<CEngine::OpenGLShader>(m_QuadShader)->setVec4("u_Color", m_QuadColor);
	CEngine::Renderer::BeginScene(m_CameraController.GetCamera());
	CEngine::Renderer::Submit(m_QuadShader, m_QuadVA);
	CEngine::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Color Settings");
	ImGui::ColorEdit4("QuadColor", glm::value_ptr(m_QuadColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(CEngine::Event& event)
{
	m_CameraController.OnEvent(event);
}
