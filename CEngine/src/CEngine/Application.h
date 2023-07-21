#pragma once
#include "Core.h"

namespace CEngine {
	class CC_API Application
	{
	public:
		Application();
		virtual ~Application();
		void run();
	};

	Application* CreateApplication();
}


