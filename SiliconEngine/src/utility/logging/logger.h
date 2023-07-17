/**
 * @file    logging.h
 *
 * @brief   Logger class.
 *
 * @author  Zachary Ning
**/

#pragma once

#include <format>
#include <string>
#include <iostream>
#include <Windows.h>

#include "utility/singleton.h"

namespace Silicon {

/**
 * @brief   Logger class.
**/
class Logger : public Singleton<Logger> {
public:
	Logger();

	~Logger();

	template <typename ...Args>
	void Debug(std::string_view msg, Args&& ...args);

	template <typename ...Args>
	void Trace(std::string_view msg, Args&& ...args);

	template <typename ...Args>
	void Info(std::string_view msg, Args&& ...args);

	template <typename ...Args>
	void Warn(std::string_view msg, Args&& ...args);

	template <typename ...Args>
	void Error(std::string_view msg, Args&& ...args);

	template <typename ...Args>
	void Fatal(std::string_view msg, Args&& ...args);

private:
	static constexpr WORD sc_defaultForeground{FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY};
	static constexpr WORD sc_defaultBackground{0};

	static constexpr WORD sc_debugForeground{0};
	static constexpr WORD sc_debugBackground{BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE};

	static constexpr WORD sc_traceForeground{FOREGROUND_INTENSITY};
	static constexpr WORD sc_traceBackground{BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE};

	static constexpr WORD sc_infoForeground{0};
	static constexpr WORD sc_infoBackground{BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY};

	static constexpr WORD sc_warnForeground{0};
	static constexpr WORD sc_warnBackground{BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY};

	static constexpr WORD sc_errorForeground{FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY};
	static constexpr WORD sc_errorBackground{BACKGROUND_RED};

	static constexpr WORD sc_fatalForeground{FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY};
	static constexpr WORD sc_fatalBackground{BACKGROUND_RED | BACKGROUND_INTENSITY};

	HANDLE m_consoleHandle;

	template <typename ...Args>
	void Log(std::string_view level, WORD foreground, WORD background,
		std::string_view msg, Args&& ...args);
};

inline Logger::Logger() {
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w+", stdout);

	SetConsoleTitle("SiliconEngine");

	m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

inline Logger::~Logger() {

}

template <typename ...Args>
inline void Logger::Log(std::string_view level, WORD foreground, WORD background,
	std::string_view msg, Args&& ...args) {
	// Print level.
	SetConsoleTextAttribute(m_consoleHandle, foreground | background);
	std::cout << "[" << level << "]";

	// Print formatted message.
	SetConsoleTextAttribute(m_consoleHandle, sc_defaultForeground | sc_defaultBackground);
	std::cout << " " << std::vformat(msg, std::make_format_args(args...)) << "\n";
}

template <typename ...Args>
inline void Logger::Debug(std::string_view msg, Args&& ...args) {
	Log("Debug", sc_debugForeground, sc_debugBackground, msg, std::forward<Args>(args)...);
}

template <typename ...Args>
inline void Logger::Trace(std::string_view msg, Args&& ...args) {
	Log("Trace", sc_traceForeground, sc_traceBackground, msg, std::forward<Args>(args)...);
}

template <typename ...Args>
void Logger::Info(std::string_view msg, Args&& ...args) {
	Log(" Info", sc_infoForeground, sc_infoBackground, msg, std::forward<Args>(args)...);
}

template <typename ...Args>
void Logger::Warn(std::string_view msg, Args&& ...args) {
	Log(" Warn", sc_warnForeground, sc_warnBackground, msg, std::forward<Args>(args)...);
}

template <typename ...Args>
void Logger::Error(std::string_view msg, Args&& ...args) {
	Log("Error", sc_errorForeground, sc_errorBackground, msg, std::forward<Args>(args)...);
}

template <typename ...Args>
void Logger::Fatal(std::string_view msg, Args&& ...args) {
	Log("Fatal", sc_fatalForeground, sc_fatalBackground, msg, std::forward<Args>(args)...);

}

}
