#pragma once
#include "Core.h"
#include "Window.h"
#include "CEngine/LayerStack.h"
#include "CEngine/Events/Event.h"
#include "CEngine/Events/ApplicationEvent.h"
#include "CEngine/Events/KeyEvent.h"
#include "CEngine/Events/MouseEvent.h"

#include "CEngine/ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

namespace CEngine {
	class CC_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() {
			return  *s_Instance;
		}
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseMoe(MouseMovedEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}


