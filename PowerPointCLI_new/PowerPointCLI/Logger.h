#pragma once
#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
	enum class Level {
		Info,
		Warning,
		Error
	};

	static Logger& instance();

	void info(const std::string& message);
	void warn(const std::string& message);
	void error(const std::string& message);

private:
	Logger();
	~Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	void log(Level level, const std::string& message);
	std::string levelToString(Level level) const;
	std::string currentTime() const;

private:
	std::ofstream file;
	std::mutex mtx;
};