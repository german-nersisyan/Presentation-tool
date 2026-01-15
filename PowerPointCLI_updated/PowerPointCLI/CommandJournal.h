#pragma once
#include "ICommandJournal.h"
#include <fstream>
#include <string>

class CommandJournal : public ICommandJournal {
	std::ofstream file;

public:
	CommandJournal(const std::string& filename = "cli.jou") {
		file.open(filename, std::ios::app);
	}

	~CommandJournal() override {
		if (file.is_open())
			file.close();
	}

	void record(const std::string& commandLine) override {
		if (file.is_open())
			file << commandLine << "\n";
	}
};