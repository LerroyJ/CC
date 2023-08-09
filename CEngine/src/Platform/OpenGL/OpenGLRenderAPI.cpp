#include "ccpch.h"
#include "OpenGLRenderAPI.h"
#include <glad/glad.h>
namespace CEngine{
	void OpenGLRenderAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void CEngine::OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void CEngine::OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void CEngine::OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void OpenGLRenderAPI::DrawArrays(const Ref<VertexArray>& vertexArray)
	{
		// TODO
		//glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetIndexBuffer()->GetCount());

		CC_ASSERT(false, "TODO: DrawArrays");
	}
}
