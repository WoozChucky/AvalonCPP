#pragma once

#include "Avalon/Core/Base.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Avalon
{
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

#define AV_CORE_TRACE(...)    ::Avalon::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AV_CORE_INFO(...)     ::Avalon::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AV_CORE_WARN(...)     ::Avalon::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AV_CORE_ERROR(...)    ::Avalon::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AV_CORE_CRITICAL(...) ::Avalon::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define AV_TRACE(...)         ::Avalon::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AV_INFO(...)          ::Avalon::Log::GetClientLogger()->info(__VA_ARGS__)
#define AV_WARN(...)          ::Avalon::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AV_ERROR(...)         ::Avalon::Log::GetClientLogger()->error(__VA_ARGS__)
#define AV_CRITICAL(...)      ::Avalon::Log::GetClientLogger()->critical(__VA_ARGS__)


