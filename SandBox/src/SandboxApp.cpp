#include <CEngine.h>

class ExampleLayer : public CEngine::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{
	}
	void OnUpdate() override
	{
		// TODO
		//CC_INFO("ExampleLayer::Update");
	}

	void OnEvent(CEngine::Event& event) override {
		CC_TRACE("{0}", event);
	}
};

class Sandbox : public CEngine::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new CEngine::ImGuiLayer());
	}
	~Sandbox() {}
};

CEngine::Application* CEngine::CreateApplication() {
	return new Sandbox();
}