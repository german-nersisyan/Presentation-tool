#include "../PowerPointCLI/Parser.h"
#include <stdexcept>

CommandData Parser::parse(const std::vector<Token>& tokens) {
	if (tokens.empty())
		throw std::runtime_error("Empty token list");

	CommandData data;
	data.name = tokens.front().text;

	for (size_t i = 1; i < tokens.size(); ++i) {
		const auto& t = tokens[i];

		if (t.type == TokenType::OPTION) {
			if (i + 1 < tokens.size() && tokens[i + 1].type == TokenType::VALUE) {
				data.options[t.text] = tokens[i + 1].text;
				++i;
			}
			else {
				throw std::runtime_error("Option without value: " + t.text);
			}
		}
		else if (t.type == TokenType::FLAG) {
			data.flags.insert(t.text);
		}
	}

	return data;
}