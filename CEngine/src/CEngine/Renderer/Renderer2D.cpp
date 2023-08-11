#include "ccpch.h"
#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
namespace CEngine {
	struct Renderer2DStorage {
		Ref<VertexArray> vertexArray;
		Ref<Shader> textureShader;
		Ref<Texture2D> whiteTexture;
	};
	static Renderer2DStorage* s_Data;
	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->textureShader = CEngine::Shader::Create("TextureShader", "assets/shaders/TextureShader.vs", "assets/shaders/TextureShader.frag");
		uint32_t whiteTextureDatat = 0xffffffff;
		s_Data->whiteTexture = CEngine::Texture2D::Create(1, 1);
		s_Data->whiteTexture->SetData(sizeof(uint32_t), &whiteTextureDatat);
		float quadVertices[] = {
			// positions        // normal         //coords    //color
			-0.5f,  0.5,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.2f, 0.1f, 0.7f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.7f, 0.1f, 0.0f,
			 0.5,   0.5,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.6f, 0.0f,
			 0.5,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.3f, 0.0f, 0.5f
		};
		uint32_t quadIndices[] = {
				0,1,3,
				0,3,2
		};
		CEngine::BufferLayout layout = {
			{"Position", CEngine::ShaderDataType::Float3},
			{"Normal",CEngine::ShaderDataType::Float3},
			{"TexCoord", CEngine::ShaderDataType::Float2},
			{"Color", CEngine::ShaderDataType::Float3}
		};
		CEngine::Ref<CEngine::VertexBuffer> vertexBuffer = CEngine::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		vertexBuffer->SetLayout(layout);
		CEngine::Ref<CEngine::IndexBuffer> indexBuffer = CEngine::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
		s_Data->vertexArray = CEngine::VertexArray::Create();
		s_Data->vertexArray->AddVertexBuffer(vertexBuffer);
		s_Data->vertexArray->SetIndexBuffer(indexBuffer);
		s_Data->vertexArray->Unbind();
	}
	void Renderer2D::ShutDown()
	{
		delete(s_Data);
	}
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->textureShader->Bind();
		s_Data->textureShader->setMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());
	}
	void Renderer2D::EndScene()
	{

	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 model = glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1), glm::vec3(size, 1));
		s_Data->whiteTexture->Bind();
		s_Data->textureShader->setMat4("u_Model", model);
		s_Data->textureShader->setVec4("u_Color", color);
		s_Data->vertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->vertexArray);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture) {
		glm::mat4 model = glm::translate(glm::mat4(1), position) * glm::scale(glm::mat4(1), glm::vec3(size, 1));
		s_Data->textureShader->setVec4("u_Color", { 1,1,1,1 });
		s_Data->textureShader->setMat4("u_Model", model);
		s_Data->textureShader->setFloat("u_xScale", size.x);
		s_Data->textureShader->setFloat("u_yScale", size.y);
		s_Data->vertexArray->Bind();
		texture->Bind();
		RenderCommand::DrawIndexed(s_Data->vertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture) {
		DrawQuad(glm::vec3(position, 0.0f), size, texture);
	}
}