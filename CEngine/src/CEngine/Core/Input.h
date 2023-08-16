#pragma once

#include "CEngine/Core/Core.h"
#include "CEngine/Core/keyCodes.h"
#include "CEngine/Core/MouseButtonCodes.h"
namespace CEngine {
	class Input {
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}