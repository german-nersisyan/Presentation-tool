#include "../PowerPointCLI/Tokenizer.h"
#include <sstream>
#include <iomanip>

std::vector<Token> Tokenizer::tokenize(const std::string& input) {
	std::vector<Token> tokens;
	std::istringstream iss(input);
	std::string word;

	bool isFirst = true;
	std::string lastOption;

	while (iss >> std::quoted(word)) {
		if (isFirst) {
			tokens.push_back({ TokenType::COMMAND, word });
			isFirst = false;
		}
		else if (word[0] == '-') {
			std::streampos pos = iss.tellg();
			std::string next;
			if (iss >> std::quoted(next)) {
				if (next[0] == '-') {
					tokens.push_back({ TokenType::FLAG, word });
					iss.seekg(pos);
				}
				else {
					tokens.push_back({ TokenType::OPTION, word });
					tokens.push_back({ TokenType::VALUE, next });
				}
			}
			else {
				tokens.push_back({ TokenType::FLAG, word });
			}
		}
	}

	return tokens;
}