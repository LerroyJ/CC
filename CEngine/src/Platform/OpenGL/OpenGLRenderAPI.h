#pragma once
#include "CEngine/Renderer/RendererAPI.h"
namespace CEngine {
	class OpenGLRenderAPI : public RendererAPI{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) override;
		virtual void DrawArrays(const Ref<VertexArray>& vertexArray) override;
	};
}