#include "ccpch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"
namespace CEngine {
	VertexArray* VertexArray::Create() {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			CC_CORE_ASSERT(false, "RendererAPI::None is currently not support");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}
		CC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}