#include "Commands.h"
/* ===================== AddSlide ===================== */

AddSlideCommand::AddSlideCommand(const std::string& t, Model& m, IView& v)
	: title(t), model(m), view(v) {}

void AddSlideCommand::execute() {
	createdIndex = model.addSlide(title);
	view.showAddedSlide(title, model.getSlideCount());
}

void AddSlideCommand::undo() {
	if (createdIndex >= 0)
		model.removeSlide(createdIndex);
}

bool AddSlideCommand::isUndoable() const {
	return true;
}

/* ===================== RemoveSlide ===================== */

RemoveSlideCommand::RemoveSlideCommand(int idx, Model& m, IView& v)
	: index(idx), model(m), view(v) {}

void RemoveSlideCommand::execute() {
	if (!model.isValidSlide(index)) {
		view.showInvalidSlideIndex();
		return;
	}

	removedTitle = model.getSlideTitle(index);
	removedShapes = model.getShapes(index);
	removed = model.removeSlide(index);

	view.showRemovedSlide(std::to_string(index));
}

void RemoveSlideCommand::undo() {
	if (removed) {
		model.insertSlide(index, removedTitle, removedShapes);
	}
}

bool RemoveSlideCommand::isUndoable() const {
	return true;
}

/* ===================== AddShape ===================== */

AddShapeCommand::AddShapeCommand(
	const std::map<std::string, std::string>& opts,
	const std::set<std::string>& fl,
	Model& m, IView& v)
	: options(opts), flags(fl), model(m), view(v) {}

void AddShapeCommand::execute() {
	if (!model.hasSlides()) {
		view.showCannotAddShapeNoSlide();
		return;
	}

	std::string type = options.count("-type") ? options.at("-type") : "rectangle";
	std::string color = options.count("-color") ? options.at("-color") : "black";
	bool filled = flags.count("-filled") > 0;

	std::shared_ptr<IShape> shape;

	if (type == "rectangle") {
		int w = options.count("-width") ? std::stoi(options.at("-width")) : 100;
		int h = options.count("-height") ? std::stoi(options.at("-height")) : 50;
		shape = std::make_shared<RectangleShape>(w, h, color, filled);
	}
	else if (type == "square") {
		int s = options.count("-size") ? std::stoi(options.at("-size")) : 50;
		shape = std::make_shared<SquareShape>(s, color, filled);
	}
	else if (type == "triangle") {
		int s = options.count("-side") ? std::stoi(options.at("-side")) : 50;
		shape = std::make_shared<TriangleShape>(s, color, filled);
	}
	else if (type == "circle") {
		int r = options.count("-radius") ? std::stoi(options.at("-radius")) : 25;
		int x = options.count("-x") ? std::stoi(options.at("-x")) : 0;
		int y = options.count("-y") ? std::stoi(options.at("-y")) : 0;
		shape = std::make_shared<CircleShape>(r, x, y, filled);
	}
	else {
		view.showMessage("Unknown shape type: " + type);
		return;
	}

	model.addShapeToCurrentSlide(shape);
}

void AddShapeCommand::undo() {
	model.removeLastShapeFromCurrentSlide();
}

bool AddShapeCommand::isUndoable() const {
	return true;
}

/* ===================== ListSlides ===================== */

ListSlidesCommand::ListSlidesCommand(Model& m, IView& v)
	: model(m), view(v) {}

void ListSlidesCommand::execute() {
	int count = model.getSlideCount();
	if (count == 0) {
		view.showNoSlides();
		return;
	}

	for (int i = 0; i < count; ++i)
		view.showSlide(i, model.getSlideTitle(i));
}

void ListSlidesCommand::undo() {}

bool ListSlidesCommand::isUndoable() const {
	return false;
}

/* ===================== Help ===================== */

HelpCommand::HelpCommand(IView& v, CommandRegistry& r)
	: view(v), registry(r) {}

void HelpCommand::execute() {
	view.showMessage("Available commands:");
	for (const auto& name : registry.getAllCommandNames())
		view.showMessage("  " + name);
}

void HelpCommand::undo() {}

bool HelpCommand::isUndoable() const {
	return false;
}

/* ===================== MoveShapeCommand ===================== */
MoveShapeCommand::MoveShapeCommand(Model& m, IView& v, int sIdx, int shIdx, int x, int y)
	: model(m), view(v), slideIndex(sIdx), shapeIndex(shIdx), newX(x), newY(y) {}

void MoveShapeCommand::execute() {
	auto& shapes = model.getShapes(slideIndex);
	if (slideIndex < 0 || slideIndex >= model.getSlideCount() ||
		shapeIndex < 0 || shapeIndex >= static_cast<int>(shapes.size())) {
		view.showMessage("Invalid slide or shape index");
		return;
	}

	// Logical "move" only
	oldX = oldY = 0; // Default origin
	moved = true;

	view.showMessage("Pretend moving shape to (" + std::to_string(newX) + "," + std::to_string(newY) + ")");
}

void MoveShapeCommand::undo() {
	if (!moved) return;

	view.showMessage("Undo: Shape returned to (" + std::to_string(oldX) + "," + std::to_string(oldY) + ")");
}

bool MoveShapeCommand::isUndoable() const {
	return true;
}

/* ===================== DeleteShapeCommand ===================== */
DeleteShapeCommand::DeleteShapeCommand(Model& m, IView& v, int sIdx, int shIdx)
	: model(m), view(v), slideIndex(sIdx), shapeIndex(shIdx) {}

void DeleteShapeCommand::execute() {
	auto& shapes = model.getShapes(slideIndex);
	if (slideIndex < 0 || slideIndex >= model.getSlideCount() ||
		shapeIndex < 0 || shapeIndex >= static_cast<int>(shapes.size())) {
		view.showMessage("Invalid slide or shape index");
		return;
	}

	removedShape = shapes[shapeIndex];
	model.removeShape(slideIndex, shapeIndex);
	deleted = true;

	view.showMessage("Shape deleted");
}

void DeleteShapeCommand::undo() {
	if (!deleted) return;

	model.addShape(slideIndex, shapeIndex, removedShape);
	view.showMessage("Undo: Shape restored");
}

bool DeleteShapeCommand::isUndoable() const {
	return true;
}