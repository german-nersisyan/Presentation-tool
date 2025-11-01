#pragma once
#include "ICommandFactory.h"
#include "Commands.h"
#include "Model.h"
#include "IView.h"
#include <memory>
#include <map>
#include <set>
#include <string>

class AddSlideFactory : public ICommandFactory {
public:
	std::unique_ptr<ICommand> create(
		const std::map<std::string, std::string>& options,
		const std::set<std::string>& flags,
		Model& model,
		IView& view) override
	{
		std::string title = options.count("-title") ? options.at("-title") : "Untitled Slide";
		return std::make_unique<AddSlideCommand>(title, model, view);
	}
};

class RemoveSlideFactory : public ICommandFactory {
public:
	std::unique_ptr<ICommand> create(
		const std::map<std::string, std::string>& options,
		const std::set<std::string>& flags,
		Model& model,
		IView& view) override
	{
		int index = options.count("-index") ? std::stoi(options.at("-index")) : -1;
		return std::make_unique<RemoveSlideCommand>(index, model, view);
	}
};

class AddShapeFactory : public ICommandFactory {
public:
	std::unique_ptr<ICommand> create(
		const std::map<std::string, std::string>& options,
		const std::set<std::string>& flags,
		Model& model,
		IView& view) override
	{
		return std::make_unique<AddShapeCommand>(options, flags, model, view);
	}
};

class ListSlidesFactory : public ICommandFactory {
public:
	std::unique_ptr<ICommand> create(
		const std::map<std::string, std::string>& /*options*/,
		const std::set<std::string>& /*flags*/,
		Model& model,
		IView& view) override
	{
		return std::make_unique<ListSlidesCommand>(model, view);
	}
};

class HelpFactory : public ICommandFactory {
	CommandRegistry& registry;

public:
	HelpFactory(CommandRegistry& r) : registry(r) {}

	std::unique_ptr<ICommand> create(
		const std::map<std::string, std::string>& /*options*/,
		const std::set<std::string>& /*flags*/,
		Model& /*model*/,
		IView& view) override
	{
		return std::make_unique<HelpCommand>(view, registry);
	}
};

class ShowSlideFactory : public ICommandFactory {
public:
	std::unique_ptr<ICommand> create(
		const std::map<std::string, std::string>& options,
		const std::set<std::string>& flags,
		Model& model,
		IView& view) override
	{
		bool showAll = flags.count("-all") > 0;
		int index = 0;
		if (options.count("-index"))
			index = std::stoi(options.at("-index"));
		return std::make_unique<ShowSlideCommand>(model, view, index, showAll);
	}
};