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

	// Temp
	CEngine::Ref<CEngine::Texture2D> m_CheckerboardTexture;
	CEngine::Ref<CEngine::Texture2D> m_FloorTexture;
	glm::vec3 m_CheckerboardPos = { 0.0f, 0.0f , -0.9f};
	glm::vec2 m_CheckerboardSize = { 3.0f, 3.0f };

	glm::vec4 m_QuadAColor = { 0.9f, 0.1f, 0.2f, 1.0f };
	glm::vec2 m_QuadAPos = { 1.0f, 0.0f };
	glm::vec2 m_QuadASize = { 0.3f, 0.3f };

	glm::vec4 m_QuadBColor = { 0.1f, 0.9f, 0.2f, 1.0f };
	glm::vec2 m_QuadBPos = { 0.0f, 0.0f };
	glm::vec2 m_QuadBSize = { 0.3f, 0.3f };

	glm::vec4 m_QuadCColor = { 0.1f, 0.1f, 0.9f, 1.0f };
	glm::vec2 m_QuadCPos = { 0.0f, 1.0f };
	glm::vec2 m_QuadCSize = { 0.3f, 0.3f };
	float m_QuadRotation = 8.05f;

	int m_Count = 10;

	CEngine::Ref<CEngine::Framebuffer> m_Framebuffer;
};