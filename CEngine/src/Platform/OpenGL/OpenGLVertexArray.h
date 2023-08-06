#pragma once
#include "CEngine/Renderer/VertexArray.h"
namespace CEngine {
	class OpenGLVertexArray : public VertexArray {
	public:	
		OpenGLVertexArray();

		virtual ~OpenGLVertexArray() {}

		virtual void Bind() const override;

		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;

		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		inline virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffer() override { return m_VertexBuffers; }

		inline virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() override { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

		
	};
}