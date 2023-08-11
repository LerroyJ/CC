#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnUpdate(CEngine::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
	CEngine::RenderCommand::Clear();
	CEngine::RenderCommand::SetClearColor({ 0.1, 0.2, 0.3, 1.0 });
	CEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	CEngine::Renderer2D::DrawQuad(m_FloorPos, m_FloorSize, m_FloorTexture);
	CEngine::Renderer2D::DrawQuad(m_QuadPos, m_QuadSize, m_QuadColor);
	CEngine::Renderer2D::EndScene();

	//std::dynamic_pointer_cast<CEngine::OpenGLShader>(m_QuadShader)->setMat4("u_ViewProjectionMatrix", m_CameraController.GetCamera().GetViewProjectionMatrix());
	//std::dynamic_pointer_cast<CEngine::OpenGLShader>(m_QuadShader)->setVec4("u_Color", m_QuadColor);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Floor Settings");
	ImGui::DragFloat3("FloorPos", glm::value_ptr(m_FloorPos), 0.05f);
	ImGui::DragFloat2("FloorSize", glm::value_ptr(m_FloorSize), 0.05f);
	ImGui::End();

	ImGui::Begin("Quad Settings");
	ImGui::DragFloat2("QuadPos", glm::value_ptr(m_QuadPos), 0.05f);
	ImGui::DragFloat2("QuadSize", glm::value_ptr(m_QuadSize), 0.05f);
	ImGui::ColorEdit4("QuadColor", glm::value_ptr(m_QuadColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(CEngine::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnAttach()
{
	m_FloorTexture = CEngine::Texture2D::Create("assets/textures/floor.jpg");
}

void Sandbox2D::OnDetach()
{
}
