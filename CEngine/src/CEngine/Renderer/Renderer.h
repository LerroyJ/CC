#pragma once
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"
namespace CEngine {
	class Renderer {
	public:
		static void BeginScene(OrthograhpicCamera& camera);

		static void EndScene();

		static void Submit(const std::shared_ptr<Shader> shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& model = glm::mat4(1));

		inline static RendererAPI::API GetAPI(){ return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};
}