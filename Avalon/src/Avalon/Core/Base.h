#pragma once

#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define AV_PLATFORM_WINDOWS 1
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define AV_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define AV_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
	 /* We also have to check __ANDROID__ before __linux__
	  * since android is based on the linux kernel
	  * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define AV_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define AV_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
		/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

#ifdef AV_PLATFORM_WINDOWS
#if AV_DYNAMIC_LINK
	#ifdef AV_BUILD_DLL
		#define AVALON_API __declspec(dllexport)
	#else
		#define AVALON_API __declspec(dllimport)
	#endif
#else
	#define AVALON_API
#endif
#else
	#error Avalon only supports Windows!
#endif

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

#ifdef AV_ENABLE_ASSERTS
	#define AV_ASSERT(x, ...) { if(!(x)) { AV_ERROR("Assertion Failed: {0}", __VA_ARGS__); AV_DEBUGBREAK(); } }
	#define AV_CORE_ASSERT(x, ...) { if(!(x)) { AV_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); AV_DEBUGBREAK(); } }
#else
	#define AV_ASSERT(x, ...)
	#define AV_CORE_ASSERT(x, ...)
#endif

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