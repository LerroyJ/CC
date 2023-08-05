#pragma once
#include "CEngine/Renderer/Buffer.h"

namespace CEngine {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() override;
		virtual void Unbind() override;
	private:
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() override;
		virtual void Unbind() override;
		inline virtual uint32_t GetCount() const override{ return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}