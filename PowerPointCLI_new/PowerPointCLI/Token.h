#pragma once
#include <string>

enum class TokenType {
	COMMAND,
	OPTION,
	VALUE,
	FLAG
};

struct Token {
	TokenType type;
	std::string text;
};