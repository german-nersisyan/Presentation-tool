#pragma once
#include "ICommand.h"
#include "Model.h"
#include "IView.h"
#include "IShape.h"
#include "CommandRegistry.h"
#include <string>
#include <map>
#include <set>
#include <memory>

class AddSlideCommand : public ICommand {
	std::string title;
	Model& model;
	IView& view;

public:
	AddSlideCommand(const std::string& t, Model& m, IView& v);

	void execute() override;
};

class RemoveSlideCommand : public ICommand {
	int index;
	Model& model;
	IView& view;

public:
	RemoveSlideCommand(int idx, Model& m, IView& v);

	void execute() override;
};

class AddShapeCommand : public ICommand {
	std::map<std::string, std::string> options;
	std::set<std::string> flags;
	Model& model;
	IView& view;

public:
	AddShapeCommand(
		const std::map<std::string, std::string>& opts,
		const std::set<std::string>& fl,
		Model& m, IView& v);

	void execute() override;
};

class ListSlidesCommand : public ICommand {
	Model& model;
	IView& view;

public:
	ListSlidesCommand(Model& m, IView& v);

	void execute() override;
};

class HelpCommand : public ICommand {
	IView& view;
	CommandRegistry& registry;

public:
	HelpCommand(IView& v, CommandRegistry& r)
		: view(v), registry(r) {}

	void execute() override;
};

class ShowSlideCommand : public ICommand {
	Model& model;
	IView& view;
	int index;
	bool showAll;

public:
	ShowSlideCommand(Model& m, IView& v, int idx = 0, bool all = false)
		: model(m), view(v), index(idx), showAll(all) {}

	void execute() override;
};