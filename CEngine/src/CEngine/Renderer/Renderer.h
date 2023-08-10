#pragma once
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"
namespace CEngine {
	class Renderer {
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& camera);

		static void EndScene();

		static void Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& model = glm::mat4(1));

		inline static RendererAPI::API GetAPI(){ return RendererAPI::GetAPI(); }
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};
		static Ref<SceneData> m_SceneData;
	};
}