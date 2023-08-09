#pragma once
#include "Window.h"
#include "CEngine/LayerStack.h"
#include "CEngine/Core/Timestep.h"

#include "CEngine/Events/Event.h"
#include "CEngine/Events/ApplicationEvent.h"
#include "CEngine/Events/KeyEvent.h"
#include "CEngine/Events/MouseEvent.h"

#include "CEngine/ImGui/ImGuiLayer.h"
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

		float m_LastFrameTime = 0.f;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}


