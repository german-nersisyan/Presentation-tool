#pragma once
#include "ICommandFactory.h"
#include <map>
#include <memory>
#include <string>
#include <stdexcept>

class CommandRegistry {
	std::map<std::string, std::unique_ptr<ICommandFactory>> factories;

public:
	CommandRegistry() = default;

	void registerFactory(const std::string& name, std::unique_ptr<ICommandFactory> factory) {
		factories[name] = std::move(factory);
	}

	ICommandFactory& getFactory(const std::string& name) {
		auto it = factories.find(name);
		if (it == factories.end())
			throw std::runtime_error("Command not found: " + name);
		return *it->second;
	}

	std::vector<std::string> getAllCommandNames() const {
		std::vector<std::string> names;
		for (const auto& pair : factories) {
			names.push_back(pair.first);
		}
		return names;
	}
};