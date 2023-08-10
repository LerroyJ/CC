#include "ccpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace CEngine {
	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<OpenGLRenderAPI>();
}