#include "Sandbox2D.h"
#include "Random.h"
Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
	CEngine::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = CEngine::Framebuffer::Create(fbSpec);
}

void Sandbox2D::OnUpdate(CEngine::Timestep ts)
{
	m_Framebuffer->Bind();
	m_CameraController.OnUpdate(ts);
	CEngine::RenderCommand::Clear();
	CEngine::RenderCommand::SetClearColor({ 0.1, 0.2, 0.3, 1.0 });
	CEngine::Renderer2D::ResetStats();
	CEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	//CEngine::Renderer2D::DrawQuad(m_CheckerboardPos, m_CheckerboardSize, m_CheckerboardTexture);
	CEngine::Renderer2D::DrawRotatedQuad(m_QuadAPos, m_QuadASize, m_QuadRotation, m_QuadAColor);
	CEngine::Renderer2D::DrawRotatedQuad(m_QuadBPos, m_QuadBSize, m_QuadRotation, m_QuadBColor);
	CEngine::Renderer2D::DrawRotatedQuad(m_QuadCPos, m_QuadCSize, m_QuadRotation, m_QuadCColor);
	CEngine::Renderer2D::EndScene();
	CEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (int x = 0; x < m_Count; x++)
		for (int y = 0; y < m_Count; y++)
			CEngine::Renderer2D::DrawRotatedQuad({ x - (float)m_Count / 2.0f,y - (float)m_Count / 2.0f }, { 0.8f,0.8f }, m_QuadRotation, m_CheckerboardTexture);
	CEngine::Renderer2D::DrawQuad({ 0,0 }, { 1.8f,1.8f }, m_FloorTexture);
	CEngine::Renderer2D::EndScene();
	m_Framebuffer->Unbind();
}

void Sandbox2D::OnImGuiRender()
{
	// Note: Switch this to true to enable dockspace
	static bool dockingEnabled = true;
	if (dockingEnabled)
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) CEngine::Application::Get().Close();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = CEngine::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_QuadAColor));

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		CEngine::FramebufferSpecification sbc = m_Framebuffer->GetSpecification();
		ImGui::Image((void*)textureID, ImVec2{ (float)sbc.Width, (float)sbc.Height });
		ImGui::End();

		ImGui::End();
}
	else
	{
		ImGui::Begin("Settings");

		auto stats = CEngine::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_QuadAColor));

		uint32_t textureID = m_CheckerboardTexture->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
		ImGui::End();
	}
#if CC_OLD
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
	ImGui::TextColored({ 1,0,0,1 }, "State");
	auto stats = CEngine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();
#endif
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
