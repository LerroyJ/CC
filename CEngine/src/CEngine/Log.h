#pragma once
#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace CEngine {
	class CC_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define CC_CORE_ERROR(...)	::CEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CC_CORE_WARN(...)	::CEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CC_CORE_INFO(...)	::CEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CC_CORE_TRACE(...)	::CEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CC_CORE_DEBUG(...)	::CEngine::Log::GetCoreLogger()->debug(__VA_ARGS__)

// Client log macros
#define CC_ERROR(...)	::CEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define CC_WARN(...)	::CEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CC_INFO(...)	::CEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define CC_TRACE(...)	::CEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CC_DEBUG(...)	::CEngine::Log::GetClientLogger()->debug(__VA_ARGS__)