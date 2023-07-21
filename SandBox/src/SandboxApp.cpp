#include <CEngine.h>

class Sandbox : public CEngine::Application {
public:
	Sandbox() {}
	~Sandbox() {}
};

CEngine::Application* CEngine::CreateApplication() {
	return new Sandbox();
}