#pragma once
#include "RenderCommand.h"
namespace CEngine {
	class Renderer {
	public:
		static void Init();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene();

		static void EndScene();

		static void Submit();

		static RendererAPI::API GetAPI(){ return RendererAPI::GetAPI(); }
	private:
	};
}