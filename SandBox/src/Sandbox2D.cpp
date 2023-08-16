#include "Sandbox2D.h"
Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnUpdate(CEngine::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
	CEngine::RenderCommand::Clear();
	CEngine::RenderCommand::SetClearColor({ 1.0f,0.0f,0.0f,1.0f });

	CEngine::Renderer2D::ResetStats();
	CEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for(uint32_t i = 0; i < 100; i++)
		CEngine::Renderer2D::DrawQuad({ i,0,0 }, { .5f,.5f }, { 0,1,0,1 });
	CEngine::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	auto stats = CEngine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
}

void Sandbox2D::OnEvent(CEngine::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnAttach()
{
}

void Sandbox2D::OnDetach()
{
}
