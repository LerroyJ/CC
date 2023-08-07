#include "ccpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>
namespace CEngine{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case CEngine::ShaderDataType::Float:
			return GL_FLOAT;
		case CEngine::ShaderDataType::Float2:
			return GL_FLOAT;
		case CEngine::ShaderDataType::Float3:
			return GL_FLOAT;
		case CEngine::ShaderDataType::Float4:
			return GL_FLOAT;
		case CEngine::ShaderDataType::Mat3:
			return GL_FLOAT;
		case CEngine::ShaderDataType::Mat4:
			return GL_FLOAT;
		case CEngine::ShaderDataType::Int:
			return GL_INT;
		case CEngine::ShaderDataType::Int2:
			return GL_INT;
		case CEngine::ShaderDataType::Int3:
			return GL_INT;
		case CEngine::ShaderDataType::Int4:
			return GL_INT;
		case CEngine::ShaderDataType::Bool:
			return GL_BOOL;
		}
		CC_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void CEngine::OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void CEngine::OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void CEngine::OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		CC_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		BufferLayout layout = vertexBuffer->GetLayout();
		for (auto& element : layout.GetElements()) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE: GL_FALSE,
				layout.GetStride(),
				(void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void CEngine::OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}
