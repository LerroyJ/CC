#include "ccpch.h"
#include "OpenGLContext.h"
#include "GLFW/glfw3.h"
#include<glad/glad.h>

namespace CEngine {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :
		m_windowHandle(windowHandle)
	{
		CC_CORE_ASSERT(windowHandle, "Window handle is null!");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CC_CORE_ASSERT(status, "Failed to initialize Glad!");
		CC_CORE_INFO("CEngine Vendor : {0}", (char*)glGetString(GL_VENDOR));
		CC_CORE_INFO("CEngine Renderer : {0}", (char*)glGetString(GL_RENDERER));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}