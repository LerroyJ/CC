#pragma once
#include "CEngine.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
class Sandbox2D : public CEngine::Layer {
public:
	Sandbox2D();
	virtual void OnUpdate(CEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(CEngine::Event& event) override;
private:
	CEngine::OrthographicCameraController m_CameraController;
	glm::vec4 m_QuadColor = { 0.6f,0.2f,0.2f,1.0f };
	CEngine::Ref<CEngine::Shader> m_QuadShader;
	CEngine::Ref<CEngine::VertexArray> m_QuadVA;
};