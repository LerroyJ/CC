#pragma once
#include "CEngine.h"
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
};