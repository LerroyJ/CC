#pragma once
#include "CEngine/Layer.h"

#include "CEngine/Events/Event.h"
#include "CEngine/Events/MouseEvent.h"
#include "CEngine/Events/KeyEvent.h"
#include "CEngine/Events/ApplicationEvent.h"
namespace CEngine {
	class CC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseScrolledEvent(MouseScrooledEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		
		bool OnWndowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}

