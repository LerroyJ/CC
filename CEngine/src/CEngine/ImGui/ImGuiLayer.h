#pragma once
#include "CEngine/Core/Layer.h"

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
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = true;
	};
}

