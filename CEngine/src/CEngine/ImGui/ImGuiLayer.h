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

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}

