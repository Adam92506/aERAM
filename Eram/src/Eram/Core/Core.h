#pragma once

#include "Eram/Core/Log.h"
#include "Eram/Debug/Instrumentor.h"

#ifdef ER_ENABLE_ASSERTS
	#define ER_ASSERT(x, ...) { if(!x) { ER_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ER_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ER_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Eram {

	template<typename T>
	using Unique = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Unique<T> CreateUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}