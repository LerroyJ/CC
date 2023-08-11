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
	glm::vec3 m_FloorPos = { 0.0f, 0.0f , -0.9f};
	glm::vec2 m_FloorSize = { 5.0f, 5.0f };
	CEngine::Ref<CEngine::Texture2D> m_FloorTexture;

	glm::vec4 m_QuadColor = { 0.9f, 0.1f, 0.2f, 1.0f };
	glm::vec2 m_QuadPos = { 0.0f, 0.0f };
	glm::vec2 m_QuadSize = { 1.0f, 1.0f };
};