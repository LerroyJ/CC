#include "ccpch.h"
#include "Renderer.h"
#include "Renderer2D.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace CEngine {
	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}



	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();
	
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