#pragma once
#include <fstream>
#include <string>

class CommandJournal {
	std::ofstream file;

public:
	CommandJournal(const std::string& filename = "cli.jou") {
		file.open(filename, std::ios::app);
	}

	~CommandJournal() {
		if (file.is_open())
			file.close();
	}

	void record(const std::string& commandLine) {
		if (file.is_open())
			file << commandLine << "\n";
	}
};