#include "ccpch.h"
#include "Renderer.h"

namespace CEngine {
	void Renderer::BeginScene()
	{
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		if (vertexArray->GetIndexBuffer() != nullptr)
			RenderCommand::DrawIndexed(vertexArray);
		else
			RenderCommand::DrawArrays(vertexArray);
	}
}