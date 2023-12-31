#pragma once
#include "Camera.h"
#include "glm/glm.hpp"
#include "Texture.h"
#include "CEngine/Renderer/EditorCamera.h"
namespace CEngine {
	class Renderer2D {
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const OrthographicCamera& camera);
		static void BeginScene(const EditorCamera& camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& tiniColor = glm::vec4(1.0));

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tiniColor = glm::vec4(1.0));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tiniColor = glm::vec4(1.0));

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size,float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size,float rotation, const glm::vec4& color);																 
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size,float rotation, const Ref<Texture2D>& texture, const glm::vec4& tiniColor = glm::vec4(1.0));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size,float rotation, const Ref<Texture2D>& texture, const glm::vec4& tiniColor = glm::vec4(1.0));
		
		struct Statistics {
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};
		static Statistics GetStats();
		static void ResetStats();
	private:
		static void FlushAndReset();
	};
}