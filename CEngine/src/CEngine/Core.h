#pragma once

#ifdef CC_PLATFORM_WINDOWS
	#ifdef CC_BUILD_DLL
		#define CC_API __declspec(dllexport)
	#else
		#define CC_API __declspec(dllimport)
	#endif // CC_BUILD_DLL
#else
	#error CC only support windows
#endif

#ifdef CC_ENABLE_ASSERTS
	#define CC_ASSERT(x, ...) {if(!(x)){CC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define CC_CORE_ASSERT(x, ...) {if(!(x)) {CC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define CC_ASSERT(x, ...)
	#define CC_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)