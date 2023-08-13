#include "ccpch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"


namespace CEngine {
	struct QuadVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};
	struct Renderer2DData {
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		Ref<VertexArray> vertexArray;
		Ref<VertexBuffer> vertexBuffer;
		Ref<Shader> textureShader;
		Ref<Shader> flatShader;
		Ref<Texture2D> whiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
	};
	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.textureShader = CEngine::Shader::Create("TextureShader", "assets/shaders/TextureShader.vs", "assets/shaders/TextureShader.frag");
		s_Data.flatShader = CEngine::Shader::Create("FlatShader", "assets/shaders/FlatShader.vs", "assets/shaders/FlatShader.frag");
		uint32_t whiteTextureDatat = 0xffffffff;
		s_Data.whiteTexture = CEngine::Texture2D::Create(1, 1);
		s_Data.whiteTexture->SetData(sizeof(uint32_t), &whiteTextureDatat);

		s_Data.vertexArray = CEngine::VertexArray::Create();
		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
		s_Data.vertexBuffer = CEngine::VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.vertexBuffer->SetLayout({
			{"Position", CEngine::ShaderDataType::Float3},
			{"Color",CEngine::ShaderDataType::Float4},
			{"TexCoord", CEngine::ShaderDataType::Float2}
			});
		s_Data.vertexArray->AddVertexBuffer(s_Data.vertexBuffer);

		uint32_t offset = 0;
		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		CEngine::Ref<CEngine::IndexBuffer> indexBuffer = CEngine::IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.vertexArray->SetIndexBuffer(indexBuffer);
		delete[] quadIndices;

	}
	void Renderer2D::ShutDown()
	{
	}
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data.flatShader->Bind();
		s_Data.flatShader->setMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
		
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.QuadIndexCount = 0;
	}
	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.vertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);
		Flush();
	}

	void Renderer2D::Flush()
	{
		s_Data.vertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.vertexArray, s_Data.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data.QuadVertexBufferPtr->Position = position + glm::vec3(-size.x / 2, -size.y / 2, 0.0f);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = position + glm::vec3(size.x/2, -size.y / 2, 0.0f);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = position + glm::vec3(size.x / 2, size.y / 2, 0.0f);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = position + glm::vec3(-size.x / 2, size.y / 2, 0.0f);
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr++;
		
		s_Data.QuadIndexCount += 6;
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tiniColor) {
		glm::mat4 model = glm::translate(glm::mat4(1), position)
			* glm::scale(glm::mat4(1), glm::vec3(size, 1));
		s_Data.textureShader->setVec4("u_Color", tiniColor);
		s_Data.textureShader->setMat4("u_Model", model);
		s_Data.textureShader->setFloat("u_xScale", size.x);
		s_Data.textureShader->setFloat("u_yScale", size.y);
		s_Data.vertexArray->Bind();
		texture->Bind();
		RenderCommand::DrawIndexed(s_Data.vertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tiniColor) {
		DrawQuad(glm::vec3(position, 0.0f), size, texture, tiniColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		glm::mat4 model = glm::translate(glm::mat4(1), position)
			* glm::rotate(glm::mat4(1), glm::radians(rotation), {0.0f, 0.0f, 1.0f})
			* glm::scale(glm::mat4(1), glm::vec3(size, 1));
		s_Data.whiteTexture->Bind();
		s_Data.textureShader->setMat4("u_Model", model);
		s_Data.textureShader->setVec4("u_Color", color);
		s_Data.vertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.vertexArray);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3(position, 0.0f), size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tiniColor) {
		glm::mat4 model = glm::translate(glm::mat4(1), position) 
			* glm::rotate(glm::mat4(1), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1), glm::vec3(size, 1));
		s_Data.textureShader->setVec4("u_Color", tiniColor);
		s_Data.textureShader->setMat4("u_Model", model);
		s_Data.textureShader->setFloat("u_xScale", size.x);
		s_Data.textureShader->setFloat("u_yScale", size.y);
		s_Data.vertexArray->Bind();
		texture->Bind();
		RenderCommand::DrawIndexed(s_Data.vertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tiniColor) {
		DrawRotatedQuad(glm::vec3(position, 0.0f), size, rotation, texture, tiniColor);
	}
}