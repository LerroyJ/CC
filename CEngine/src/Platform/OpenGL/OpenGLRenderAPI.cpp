#include "ccpch.h"
#include "OpenGLRenderAPI.h"
#include <glad/glad.h>
namespace CEngine{
	void CEngine::OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void CEngine::OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void CEngine::OpenGLRenderAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void OpenGLRenderAPI::DrawArrays(const std::shared_ptr<VertexArray>& vertexArray)
	{
		// TODO
		//glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetIndexBuffer()->GetCount());

		CC_ASSERT(false, "TODO: DrawArrays");
	}
}
