#pragma once
#ifdef CC_PLATFORM_WINDOWS

extern CEngine::Application* CEngine::CreateApplication();

int main(int argc, char** argv) {
	printf("cc test\n");
	auto app = CEngine::CreateApplication();
	app->run();
	delete app;
}
#endif
