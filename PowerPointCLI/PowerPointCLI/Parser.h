#pragma once
#include "Token.h"
#include <map>
#include <set>
#include <string>
#include <vector>

struct CommandData {
	std::string name;
	std::map<std::string, std::string> options;
	std::set<std::string> flags;
};

class Parser {
public:
	CommandData parse(const std::vector<Token>& tokens);
};