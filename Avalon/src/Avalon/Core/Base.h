#pragma once

#include "Avalon/Core/PlatformDetection.h"

#include <memory>

#ifdef AV_DEBUG
	#if defined(AV_PLATFORM_WINDOWS)
		#define AV_DEBUGBREAK() __debugbreak()
	#elif defined(AV_PLATFORM_LINUX)
		#include <signal.h>
		#define AV_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
		#define AV_ENABLE_ASSERTS
	#else
		#define AV_DEBUGBREAK()
#endif

#define AV_EXPAND_MACRO(x) x
#define AV_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


typedef float F32;
typedef double F64;

typedef char S8;
typedef unsigned char U8;

typedef short S16;
typedef unsigned short U16;

typedef int S32;
typedef unsigned int U32;

typedef long long S64;
typedef unsigned long long U64;

namespace Avalon
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
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

#include "Avalon/Core/Log.h"
#include "Avalon/Core/Assert.h"