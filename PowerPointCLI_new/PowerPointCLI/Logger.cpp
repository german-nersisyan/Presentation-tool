#include "Logger.h"
#include <chrono>
#include <iomanip>
#include <sstream>

Logger& Logger::instance() {
	static Logger logger;
	return logger;
}

Logger::Logger() {
	file.open("cli.log", std::ios::app);
}

Logger::~Logger() {
	if (file.is_open())
		file.close();
}

void Logger::info(const std::string& message) {
	log(Level::Info, message);
}

void Logger::warn(const std::string& message) {
	log(Level::Warning, message);
}

void Logger::error(const std::string& message) {
	log(Level::Error, message);
}

void Logger::log(Level level, const std::string& message) {
	std::lock_guard<std::mutex> lock(mtx);
	if (!file.is_open()) return;

	file << "[" << currentTime() << "] "
		<< levelToString(level) << " "
		<< message << "\n";
}

std::string Logger::levelToString(Level level) const {
	switch (level) {
	case Level::Info: return "INFO ";
	case Level::Warning: return "WARN ";
	case Level::Error: return "ERROR";
	}
	return "UNK  ";
}

std::string Logger::currentTime() const {
	using namespace std::chrono;

	auto now = system_clock::now();
	std::time_t t = system_clock::to_time_t(now);

	std::tm tm{};
#ifdef _WIN32
	localtime_s(&tm, &t);
#else
	localtime_r(&t, &tm);
#endif

	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}