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
	virtual void OnAttach() override;
	virtual void OnDetach() override;
private:
	CEngine::OrthographicCameraController m_CameraController;

	CEngine::Ref<CEngine::Texture2D> m_CheckerboardTexture;
	glm::vec3 m_CheckerboardPos = { 0.0f, 0.0f , -0.9f};
	glm::vec2 m_CheckerboardSize = { 3.0f, 3.0f };

	glm::vec4 m_QuadColor = { 0.9f, 0.1f, 0.2f, 1.0f };
	glm::vec2 m_QuadPos = { 0.0f, 0.0f };
	glm::vec2 m_QuadSize = { 0.3f, 0.3f };
	float m_QuadRotation = 8.05f;
};