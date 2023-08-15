#pragma once
#include "Window.h"
#include "CEngine/Core/LayerStack.h"
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

		static Application& Get() {
			return  *s_Instance;
		}
		Window& GetWindow() { return *m_Window; }
		void Close();
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseMoe(MouseMovedEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.f;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}


