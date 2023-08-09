#include "ccpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRenderAPI.h"

namespace CEngine {
	Ref<RendererAPI> RenderCommand::s_RendererAPI = std::make_shared<OpenGLRenderAPI>();
}