#pragma once
#include "Camera.h"
namespace CEngine {
	class Renderer3D
	{
	public:
		static void Init();
		static void ShutDow();

		static void BeginScene(const PerspectiveCamera& camera);
		static void EndScene();
		static void Flush();

		static void DrawCube(float ts);
		static void DrawQuad(glm::mat4& transorm, glm::vec4& color);
	};
}



