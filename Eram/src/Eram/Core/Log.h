#pragma once

#include "Eram/Core/Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Eram
{

	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

// Log Macros
#define ER_TRACE(...) ::Eram::Log::GetLogger()->trace(__VA_ARGS__)
#define ER_INFO(...) ::Eram::Log::GetLogger()->info(__VA_ARGS__)
#define ER_WARN(...) ::Eram::Log::GetLogger()->warn(__VA_ARGS__)
#define ER_ERROR(...) ::Eram::Log::GetLogger()->error(__VA_ARGS__)
#define ER_CRITICAL(...) ::Eram::Log::GetLogger()->critical(__VA_ARGS__)