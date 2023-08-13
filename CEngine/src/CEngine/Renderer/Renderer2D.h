#pragma once
#include "Camera.h"
#include "glm/glm.hpp"
#include "Texture.h"
namespace CEngine {
	class Renderer2D {
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tiniColor = glm::vec4(1.0));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tiniColor = glm::vec4(1.0));


		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size,float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size,float rotation, const glm::vec4& color);																 
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size,float rotation, const Ref<Texture2D>& texture, const glm::vec4& tiniColor = glm::vec4(1.0));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size,float rotation, const Ref<Texture2D>& texture, const glm::vec4& tiniColor = glm::vec4(1.0));
	};
}