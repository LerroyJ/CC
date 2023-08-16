#pragma once
#include "CEngine.h"

namespace CEngine {
	class EditorLayer : public CEngine::Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;

		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
	private:
		OrthographicCameraController m_CameraController;
		PerspectiveCameraController m_PerspectiveCameraController;
		// Temp
		Ref<CEngine::Texture2D> m_CheckerboardTexture;
		Ref<CEngine::Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec4 m_QuadColor;
	};
}

