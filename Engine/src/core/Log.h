#pragma once

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ALStore {

	class Log
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

// Core log macros
#define AL_CORE_TRACE(...)       ::ALStore::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AL_CORE_INFO(...)        ::ALStore::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AL_CORE_WARN(...)        ::ALStore::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AL_CORE_ERROR(...)       ::ALStore::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AL_CORE_CRITICAL(...)    ::ALStore::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define AL_TRACE(...)	          ::ALStore::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AL_INFO(...)	          ::ALStore::Log::GetClientLogger()->info(__VA_ARGS__)
#define AL_WARN(...)	          ::ALStore::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AL_ERROR(...)	          ::ALStore::Log::GetClientLogger()->error(__VA_ARGS__)
#define AL_CRITICALAL(...)	      ::ALStore::Log::GetClientLogger()->critical(__VA_ARGS__)