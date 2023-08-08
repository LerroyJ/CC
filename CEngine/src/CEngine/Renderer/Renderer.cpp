#include "ccpch.h"
#include "Renderer.h"
namespace CEngine {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	void Renderer::BeginScene(OrthograhpicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& model)
	{
		shader->Bind();
		shader->setMat4("VP", m_SceneData->ViewProjectionMatrix);
		shader->setMat4("model", model);
		vertexArray->Bind();
		if (vertexArray->GetIndexBuffer() != nullptr) {
			RenderCommand::DrawIndexed(vertexArray);
		}
		else
			RenderCommand::DrawArrays(vertexArray);
	}
}