#pragma once
#include "ICommandFactory.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class CommandRegistry {
	std::map<std::string, std::unique_ptr<ICommandFactory>> factories;

public:
	CommandRegistry() = default;

	void registerFactory(const std::string& name, std::unique_ptr<ICommandFactory> factory) {
		factories[name] = std::move(factory);
	}

	// Returns nullptr if not found
	ICommandFactory* getFactory(const std::string& name) const {
		auto it = factories.find(name);
		if (it == factories.end()) return nullptr;
		return it->second.get();
	}

	std::vector<std::string> getAllCommandNames() const {
		std::vector<std::string> names;
		for (const auto& pair : factories) {
			names.push_back(pair.first);
		}
		return names;
	}
};