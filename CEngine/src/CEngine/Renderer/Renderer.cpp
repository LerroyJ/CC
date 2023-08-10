#include "ccpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace CEngine {
	Ref<Renderer::SceneData> Renderer::m_SceneData = std::make_shared<Renderer::SceneData>();
	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& model)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setMat4("u_VP", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setMat4("u_Model", model);
		vertexArray->Bind();
		if (vertexArray->GetIndexBuffer() != nullptr) {
			RenderCommand::DrawIndexed(vertexArray);
		}
		else
			RenderCommand::DrawArrays(vertexArray);
	}
}