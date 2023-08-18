#include "ccpch.h"
#include "Renderer.h"
#include "Renderer2D.h"
#include "Renderer3D.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace CEngine {
	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
		Renderer3D::Init();
	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	
	void Renderer::BeginScene()
	{
		
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit()
	{
	}
}