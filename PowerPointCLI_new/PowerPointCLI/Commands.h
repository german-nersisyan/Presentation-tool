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

/* ===================== AddSlide ===================== */

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

/* ===================== RemoveSlide ===================== */

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

/* ===================== AddShape ===================== */

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

/* ===================== ListSlides ===================== */

class ListSlidesCommand : public ICommand {
	Model& model;
	IView& view;

public:
	ListSlidesCommand(Model& m, IView& v);

	void execute() override;
	void undo() override;
	bool isUndoable() const override;
};

/* ===================== Help ===================== */

class HelpCommand : public ICommand {
	IView& view;
	CommandRegistry& registry;

public:
	HelpCommand(IView& v, CommandRegistry& r);

	void execute() override;
	void undo() override;
	bool isUndoable() const override;
};

/* ===================== MoveShapeCommand ===================== */
class MoveShapeCommand : public ICommand {
	Model& model;
	IView& view;
	int slideIndex;
	int shapeIndex;
	int newX;
	int newY;
	bool moved = false;

	// Logical position storage for undo
	int oldX = 0;
	int oldY = 0;

public:
	MoveShapeCommand(Model& m, IView& v, int sIdx, int shIdx, int x, int y);

	void execute() override;
	void undo() override;
	bool isUndoable() const override;
};

/* ===================== DeleteShapeCommand ===================== */
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