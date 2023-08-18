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
		// Temp
		Ref<CEngine::Texture2D> m_CheckerboardTexture;
		Ref<CEngine::Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize{ 0.0f, 0.0f };
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Ref<Scene> m_Scene;

		Entity m_Entity;
		glm::vec3 m_QuadPos{0};
		glm::vec3 m_QuadSize{1};
		glm::vec3 m_QuadRotation{0};

		Entity m_CameraEntity;
		Entity m_SecondCamera;
		bool m_PrimaryCamera = true;
	};
}

