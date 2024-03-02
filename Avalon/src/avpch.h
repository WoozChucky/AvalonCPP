#pragma once

#include "Avalon/Core/PlatformDetection.h"

#ifdef AV_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Avalon/Core/Base.h"
#include "Avalon/Core/Log.h"
#include "Avalon/Debug/Instrumentor.h"

#if AV_PLATFORM_WINDOWS
	#include <Windows.h>
#endif