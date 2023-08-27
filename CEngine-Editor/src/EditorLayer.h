#pragma once
#include "CEngine.h"
#include "Panels/SceneHierarchyPanel.h"

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
		bool OnKeyPressed(KeyPressedEvent& event);
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:
		// Temp
		Ref<CEngine::Texture2D> m_CheckerboardTexture;
		Ref<CEngine::Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize{ 0.0f, 0.0f };
		bool m_ViewportFocused = false, m_ViewportHovered = false;

		Ref<Scene> m_Scene;

		Entity m_CameraEntity;
		Entity m_SecondCamera;
		bool m_PrimaryCamera = true;

		int m_GizmoType = -1;

		SceneHierarchyPanel m_SceneHierarchyPanel;
	};
}

