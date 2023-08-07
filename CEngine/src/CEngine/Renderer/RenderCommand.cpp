#include "ccpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace CEngine {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRenderAPI;
}