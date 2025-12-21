#pragma once
#include "ICommand.h"
#include "Model.h"
#include "IView.h"
#include "IShape.h"
#include "CommandRegistry.h"
#include "JSONSerializer.h"
#include <string>
#include <map>
#include <set>
#include <memory>

class AddSlideCommand : public ICommand {
	std::string title;
	Model& model;
	IView& view;
	int createdIndex = -1;

public:
	AddSlideCommand(const std::string& t, Model& m, IView& v);

	void execute() override;
	void undo() override;
	bool isUndoable() const override;
};

class RemoveSlideCommand : public ICommand {
	int index;
	Model& model;
	IView& view;

	std::string removedTitle;
	std::vector<std::shared_ptr<IShape>> removedShapes;
	bool removed = false;

public:
	RemoveSlideCommand(int idx, Model& m, IView& v);

	void execute() override;
	void undo() override;
	bool isUndoable() const override;
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
	void undo() override;
	bool isUndoable() const override;
};

class ListSlidesCommand : public ICommand {
	Model& model;
	IView& view;

public:
	ListSlidesCommand(Model& m, IView& v);

	void execute() override;
	void undo() override;
	bool isUndoable() const override;
};

class HelpCommand : public ICommand {
	IView& view;
	CommandRegistry& registry;

public:
	HelpCommand(IView& v, CommandRegistry& r);

	void execute() override;
	void undo() override;
	bool isUndoable() const override;
};

class MoveShapeCommand : public ICommand {
	Model& model;
	IView& view;
	int slideIndex;
	int shapeIndex;
	int newX;
	int newY;
	bool moved = false;

	int oldX = 0;
	int oldY = 0;

public:
	MoveShapeCommand(Model& m, IView& v, int sIdx, int shIdx, int x, int y);

	void execute() override;
	void undo() override;
	bool isUndoable() const override;
};

class DeleteShapeCommand : public ICommand {
	Model& model;
	IView& view;
	int slideIndex;
	int shapeIndex;
	std::shared_ptr<IShape> removedShape;
	bool deleted = false;

public:
	DeleteShapeCommand(Model& m, IView& v, int sIdx, int shIdx);

	void execute() override;
	void undo() override;
	bool isUndoable() const override;
};

class SaveJsonCommand : public ICommand {
	Model& model;
	IView& view;
	std::string file;
	JSONSerializer serializer;

public:
	SaveJsonCommand(const std::string& f, Model& m, IView& v)
		: file(f), model(m), view(v) {}

	void execute() override {
		if (serializer.save(model, file))
			view.showMessage("Saved presentation to " + file);
		else
			view.showMessage("Failed to save JSON");
	}

	void undo() override {}
	bool isUndoable() const override { return false; }
};

class LoadJsonCommand : public ICommand {
	Model& model;
	IView& view;
	std::string file;
	JSONSerializer serializer;

public:
	LoadJsonCommand(const std::string& f, Model& m, IView& v)
		: file(f), model(m), view(v) {}

	void execute() override {
		if (serializer.load(model, file))
			view.showMessage("Loaded presentation from " + file);
		else
			view.showMessage("Failed to load JSON");
	}

	void undo() override { }

	bool isUndoable() const override {
		return false;
	}
};