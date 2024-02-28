#pragma once

#ifdef AV_PLATFORM_WINDOWS
	#ifdef AV_BUILD_DLL
		#define AVALON_API __declspec(dllexport)
	#else
		#define AVALON_API __declspec(dllimport)
	#endif
#else
	#error Avalon only supports Windows!
#endif

#define BIT(x) (1 << x)

typedef float F32;
typedef int S32;
typedef unsigned int U32;
typedef long long S64;
typedef unsigned long long U64;