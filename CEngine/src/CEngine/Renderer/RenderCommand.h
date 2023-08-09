#pragma once
#include "RendererAPI.h"

namespace CEngine {
	class RenderCommand {
			
	public:
		inline static void Init() { s_RendererAPI->Init(); }
		inline static void SetClearColor(const glm::vec4& color) { s_RendererAPI->SetClearColor(color); }
		inline static void Clear() { s_RendererAPI->Clear(); }
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawIndexed(vertexArray); }
		inline static void DrawArrays(const Ref<VertexArray>& vertexArray) { s_RendererAPI->DrawArrays(vertexArray); }
	private:
		static Ref<RendererAPI> s_RendererAPI;
	};
}