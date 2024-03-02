#pragma once

#include "Avalon/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

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

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
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


