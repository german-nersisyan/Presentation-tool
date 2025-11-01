#pragma once
#include "ICommand.h"
#include "Model.h"
#include "IView.h"
#include <map>
#include <set>
#include <string>
#include <memory>

class ICommandFactory {
public:
	virtual ~ICommandFactory() = default;

	virtual std::unique_ptr<ICommand> create(
		const std::map<std::string, std::string>& options,
		const std::set<std::string>& flags,
		Model& model,
		IView& view) = 0;
};