#include "ccpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"
namespace CEngine {
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CC_CORE_ASSERT(false, "RendererAPI::None is currently not support");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared <OpenGLTexture2D>(path);
		}
		CC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}