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
		float TexIndex;
	};

	struct Renderer2DData {
		Ref<Shader> flatShader;
		// -----
		// indexBuffer only set once.
		// -----
		Ref<VertexArray> vertexArray;
		Ref<VertexBuffer> vertexBuffer;
		Ref<Texture2D> whiteTexture;

		static const uint32_t MaxQuads = 10000;
		// vertexBuffer and indexBuffer
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		glm::vec4 QuadVertexPosition[4];
		glm::vec2 QuadTexCoords[4];

		// textures
		static const uint32_t MaxTextureSlots = 32;	// TODO: RenderCaps

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1;	//0 = white texuter

		Renderer2D::Statistics Stats;
	};
	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		uint32_t whiteTextureDatat = 0xffffffff;
		s_Data.whiteTexture = Texture2D::Create(1, 1);
		s_Data.whiteTexture->SetData(sizeof(uint32_t), &whiteTextureDatat);
		s_Data.vertexArray = VertexArray::Create();
		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.vertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
		s_Data.vertexBuffer->SetLayout({
			{"Position", ShaderDataType::Float3},
			{"Color", ShaderDataType::Float4},
			{"TexCoord", ShaderDataType::Float2},
			{"a_TexIndex", ShaderDataType::Float}
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
		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
		s_Data.vertexArray->SetIndexBuffer(indexBuffer);
		delete[] quadIndices;

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
			samplers[i] = i;
		s_Data.flatShader = Shader::Create("FlatShader", "assets/shaders/FlatShader.vs", "assets/shaders/FlatShader.frag");
		s_Data.flatShader->Bind();
		s_Data.flatShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);
		s_Data.TextureSlots[0] = s_Data.whiteTexture;

		s_Data.QuadVertexPosition[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPosition[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPosition[2] = { 0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertexPosition[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadTexCoords[0] = { 0.0f, 0.0f };
		s_Data.QuadTexCoords[1] = { 1.0f, 0.0f };
		s_Data.QuadTexCoords[2] = { 1.0f, 1.0f };
		s_Data.QuadTexCoords[3] = { 0.0f, 1.0f };
	}
	void Renderer2D::ShutDown()
	{
	}
	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		glm::mat4 viewProj = camera.GetCamerProjection() * glm::inverse(transform);
		s_Data.flatShader->setMat4("u_ViewProjectionMatrix", viewProj);

		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.QuadIndexCount = 0;

		s_Data.TextureSlotIndex = 1;
	}
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data.flatShader->setMat4("u_ViewProjectionMatrix", camera.GetViewProjectionMatrix());

		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.QuadIndexCount = 0;

		s_Data.TextureSlotIndex = 1;
	}
	void Renderer2D::BeginScene(const EditorCamera& camera)
	{
		glm::mat4 viewProj = camera.GetViewProjection();
		s_Data.flatShader->setMat4("u_ViewProjectionMatrix", viewProj);

		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
		s_Data.QuadIndexCount = 0;

		s_Data.TextureSlotIndex = 1;
	}
	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.vertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);
		s_Data.flatShader->Bind();
		Flush();
	}

	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			s_Data.TextureSlots[i]->Bind(i);
		s_Data.vertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.vertexArray, s_Data.QuadIndexCount);

		s_Data.Stats.DrawCalls++;
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		const float textureIndex = 0.0f; // White Texture
		for (uint32_t i = 0; i < 4; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[i];
			s_Data.QuadVertexBufferPtr->Color = color;
			s_Data.QuadVertexBufferPtr->TexCoord = s_Data.QuadTexCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec4& tiniColor)
	{
		if (s_Data.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		float textureIndex = 0.0f;

		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get()) {
				textureIndex = (float)i;
				break;
			}
		}
		if (textureIndex == 0.0f) {
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		for (uint32_t i = 0; i < 4; i++) {
			s_Data.QuadVertexBufferPtr->Position = transform * s_Data.QuadVertexPosition[i];
			s_Data.QuadVertexBufferPtr->Color = tiniColor;
			s_Data.QuadVertexBufferPtr->TexCoord = s_Data.QuadTexCoords[i];
			s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
			s_Data.QuadVertexBufferPtr++;
		}

		s_Data.QuadIndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1), { size.x,size.y, 1.0f });

		DrawQuad(transform, color);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(position, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tiniColor) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1), { size.x,size.y, 1.0f });
		DrawQuad(transform, texture, tiniColor);
	}

	
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tiniColor) {
		DrawQuad(glm::vec3(position, 0.0f), size, texture, tiniColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1), { size.x,size.y, 1.0f });
		DrawQuad(transform, color);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3(position, 0.0f), size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tiniColor)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1), { size.x,size.y, 1.0f });
		DrawQuad(transform, texture, tiniColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tiniColor) {
		DrawRotatedQuad(glm::vec3(position, 0.0f), size, rotation, texture, tiniColor);
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_Data.Stats;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Renderer2D::Statistics));
	}

	void Renderer2D::FlushAndReset() 
	{
		EndScene();

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}
}