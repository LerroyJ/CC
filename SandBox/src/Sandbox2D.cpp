#include "Sandbox2D.h"
#include "Random.h"

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
	//CEngine::Renderer2D::DrawQuad(m_CheckerboardPos, m_CheckerboardSize, m_CheckerboardTexture);
	//CEngine::Renderer2D::DrawRotatedQuad(m_QuadPos, m_QuadSize, m_QuadRotation, m_QuadColor);
	CEngine::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Sandbox2D");
	ImGui::TextColored({ 1,0,0,1 }, "Floor Settings");
	ImGui::DragFloat3("FloorPos", glm::value_ptr(m_CheckerboardPos), 0.05f);
	ImGui::DragFloat2("FloorSize", glm::value_ptr(m_CheckerboardSize), 0.05f);


	ImGui::TextColored({ 1,0,0,1 }, "Quad Settings");
	ImGui::DragFloat2("QuadPos", glm::value_ptr(m_QuadPos), 0.05f);
	ImGui::DragFloat("QuadRotation", &m_QuadRotation, 0.05f);
	ImGui::DragFloat2("QuadSize", glm::value_ptr(m_QuadSize), 0.1f);
	ImGui::ColorEdit4("QuadColor", glm::value_ptr(m_QuadColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(CEngine::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = CEngine::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}
