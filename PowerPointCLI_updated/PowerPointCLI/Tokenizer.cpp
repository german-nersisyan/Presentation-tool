#include "Tokenizer.h"
#include <cctype>

// Simple tokenizer: splits on whitespace, supports quoted tokens using '"'.
// Produces a token list where the first token is COMMAND; tokens starting
// with '-' are either OPTION (if followed by a non-dash token) or FLAG.
std::vector<Token> Tokenizer::tokenize(const std::string& input) {
	std::vector<Token> tokens;
	std::vector<std::string> parts;

	// Parse input into parts handling quoted strings
	std::string cur;
	bool inQuote = false;
	for (size_t i = 0; i < input.size(); ++i) {
		char c = input[i];
		if (c == '"') {
			inQuote = !inQuote;
			continue;
		}
		if (!inQuote && std::isspace(static_cast<unsigned char>(c))) {
			if (!cur.empty()) { parts.push_back(cur); cur.clear(); }
		}
		else {
			cur.push_back(c);
		}
	}
	if (!cur.empty()) parts.push_back(cur);

	if (parts.empty()) return tokens;

	tokens.push_back({ TokenType::COMMAND, parts[0] });

	for (size_t i = 1; i < parts.size(); ++i) {
		const std::string& p = parts[i];
		if (!p.empty() && p[0] == '-') {
			if (i + 1 < parts.size() && !parts[i+1].empty() && parts[i+1][0] != '-') {
				tokens.push_back({ TokenType::OPTION, p });
				tokens.push_back({ TokenType::VALUE, parts[i+1] });
				++i; // skip value
			}
			else {
				tokens.push_back({ TokenType::FLAG, p });
			}
		}
		else {
			tokens.push_back({ TokenType::VALUE, p });
		}
	}

	return tokens;
}