#include "Parser.h"
#include <stdexcept>

CommandData Parser::parse(const std::vector<Token>& tokens) {
	CommandData data;
	if (tokens.empty()) return data;

	data.name = tokens.front().text;

	for (size_t i = 1; i < tokens.size(); ++i) {
		const auto& t = tokens[i];

		if (t.type == TokenType::OPTION) {
			if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::VALUE) {
				data.options[t.text] = tokens[i + 1].text;
				++i;
			}
			else {
				// Treat option without explicit value as a flag-like option with empty string
				data.options[t.text] = std::string();
			}
		}
		else if (t.type == TokenType::FLAG) {
			data.flags.insert(t.text);
		}
		else if (t.type == TokenType::VALUE) {
			// stray value without an option - ignore or could be positional
		}
	}

	return data;
}