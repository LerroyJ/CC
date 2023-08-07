#include "ccpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace CEngine
{
	Shader::~Shader()
	{
	}
	Shader* Shader::Create(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			CC_CORE_ASSERT(false, "RendererAPI::None is currently not support");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexPath, fragmentPath, geometryPath);
		}
		CC_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
