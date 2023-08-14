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
	CEngine::Renderer2D::DrawQuad(m_QuadAPos, m_QuadASize, m_QuadAColor);
	CEngine::Renderer2D::DrawQuad(m_QuadBPos, m_QuadBSize, m_QuadBColor);
	CEngine::Renderer2D::DrawQuad(m_QuadCPos, m_QuadCSize, m_QuadCColor);
	for (int x = 0; x < m_Count; x++)
		for (int y = 0; y < m_Count; y++)
			CEngine::Renderer2D::DrawQuad({ x - m_Count / 2,y - m_Count / 2 }, { 0.8f,0.8f }, m_CheckerboardTexture);
	CEngine::Renderer2D::DrawQuad({ 0,0 }, { 1.8f,1.8f }, m_FloorTexture);
	CEngine::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Sandbox2D");
	ImGui::TextColored({ 1,0,0,1 }, "Floor Settings");
	ImGui::DragFloat3("FloorPos", glm::value_ptr(m_CheckerboardPos), 0.05f);
	ImGui::DragFloat2("FloorSize", glm::value_ptr(m_CheckerboardSize), 0.05f);


	ImGui::TextColored({ 1,0,0,1 }, "QuadA Settings");
	ImGui::DragFloat2("QuadAPos", glm::value_ptr(m_QuadAPos), 0.05f);
	ImGui::DragFloat2("QuadASize", glm::value_ptr(m_QuadASize), 0.1f);
	ImGui::ColorEdit4("QuadAColor", glm::value_ptr(m_QuadAColor));
	ImGui::TextColored({ 1,0,0,1 }, "QuadB Settings");
	ImGui::DragFloat2("QuadBPos", glm::value_ptr(m_QuadBPos), 0.05f);
	ImGui::DragFloat2("QuadBSize", glm::value_ptr(m_QuadBSize), 0.1f);
	ImGui::ColorEdit4("QuadBColor", glm::value_ptr(m_QuadBColor));
	ImGui::TextColored({ 1,0,0,1 }, "QuadC Settings");
	ImGui::DragFloat2("QuadCPos", glm::value_ptr(m_QuadCPos), 0.05f);
	ImGui::DragFloat2("QuadCSize", glm::value_ptr(m_QuadCSize), 0.1f);
	ImGui::ColorEdit4("QuadCColor", glm::value_ptr(m_QuadCColor));
	ImGui::DragFloat("QuadRotation", &m_QuadRotation, 0.05f);
	ImGui::SliderInt("count", &m_Count, 1, 100);
	ImGui::End();
}

void Sandbox2D::OnEvent(CEngine::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = CEngine::Texture2D::Create("assets/textures/Checkerboard.png");
	m_FloorTexture = CEngine::Texture2D::Create("assets/textures/floor.jpg");
}

void Sandbox2D::OnDetach()
{
}
