#pragma once
#include "Token.h"
#include <vector>
#include <string>

class Tokenizer {
public:
	std::vector<Token> tokenize(const std::string& input);
};