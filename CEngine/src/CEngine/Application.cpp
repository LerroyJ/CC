#include "ccpch.h"
#include "Application.h"
#include "CEngine/Log.h"

#include "glad/glad.h"
#include "imgui.h"
namespace CEngine {
	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		//dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		//dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(OnMouseMoe));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::run() {
		while (m_Running) {
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			m_Window->OnUpdate();
		};
	}

	bool Application::OnWindowClosed(WindowCloseEvent& event) {
		CC_CORE_TRACE("{0}", event);
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event) {
		CC_CORE_TRACE("{0}", event);
		return true;
	}

	bool Application::OnMouseMoe(MouseMovedEvent& event) {
		CC_CORE_TRACE("{0}", event);
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
}
