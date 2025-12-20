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

class MoveShapeFactory : public ICommandFactory {
public:
	std::unique_ptr<ICommand> create(
		const std::map<std::string, std::string>& options,
		const std::set<std::string>& flags,
		Model& model,
		IView& view) override
	{
		int slideIndex = options.count("-index") ? std::stoi(options.at("-index")) : 0;
		int shapeIndex = options.count("-shape") ? std::stoi(options.at("-shape")) : 0;
		int x = options.count("-x") ? std::stoi(options.at("-x")) : 0;
		int y = options.count("-y") ? std::stoi(options.at("-y")) : 0;

		return std::make_unique<MoveShapeCommand>(model, view, slideIndex, shapeIndex, x, y);
	}
};

class DeleteShapeFactory : public ICommandFactory {
public:
	std::unique_ptr<ICommand> create(
		const std::map<std::string, std::string>& options,
		const std::set<std::string>& flags,
		Model& model,
		IView& view) override
	{
		int slideIndex = options.count("-index") ? std::stoi(options.at("-index")) : 0;
		int shapeIndex = options.count("-shape") ? std::stoi(options.at("-shape")) : 0;

		return std::make_unique<DeleteShapeCommand>(model, view, slideIndex, shapeIndex);
	}
};


/*class ShowSlideFactory : public ICommandFactory {
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
};*/