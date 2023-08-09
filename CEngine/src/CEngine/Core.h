#pragma once
#include <memory>
#ifdef CC_PLATFORM_WINDOWS
#if CC_DYNAMIC_LINK
	#ifdef CC_BUILD_DLL
		#define CC_API __declspec(dllexport)
	#else
		#define CC_API __declspec(dllimport)
	#endif // CC_BUILD_DLL
#else
	#define CC_API
#endif
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

namespace CEngine {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}