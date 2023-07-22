#pragma once
#ifdef CC_PLATFORM_WINDOWS

extern CEngine::Application* CEngine::CreateApplication();

int main(int argc, char** argv) {
	CEngine::Log::Init();
	CC_DEBUG("this is debug log!");
	auto app = CEngine::CreateApplication();
	app->run();
	delete app;
}
#endif
