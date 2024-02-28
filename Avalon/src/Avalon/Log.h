#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Avalon
{
	class AVALON_API Log
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


