#pragma once
#include "Buffer.h"

namespace CEngine {
	class VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		virtual std::vector<Ref<VertexBuffer>> GetVertexBuffer() = 0;
		virtual Ref<IndexBuffer> GetIndexBuffer() = 0;

		static Ref<VertexArray> Create();
	};
}