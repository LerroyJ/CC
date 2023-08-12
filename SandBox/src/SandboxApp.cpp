#include <CEngine.h>
#include "imgui/imgui.h"
#include<CEngine/Core/EntryPoint.h>
#include "Platform/OpenGL/OpenGLShader.h"
#include "Sandbox2D.h"

class Sandbox : public CEngine::Application {
public:
	Sandbox() {
		PushLayer(new Sandbox2D());
	}
	~Sandbox() {}
};

CEngine::Application* CEngine::CreateApplication() {
	return new Sandbox();
}