#include "Commands.h"

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


void AddShapeCommand::execute() {
	if (!model.hasSlides()) {
		view.showCannotAddShapeNoSlide();
		return;
	}

	if (!shape) {
		view.showMessage("No shape provided");
		return;
	}

	if (!model.addShapeToCurrentSlide(shape)) {
		view.showMessage("Failed to add shape to current slide");
		return;
	}
}

void AddShapeCommand::undo() {
	model.removeLastShapeFromCurrentSlide();
}

bool AddShapeCommand::isUndoable() const {
	return true;
}


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


ShowSlidesCommand::ShowSlidesCommand(Model& m, IView& v, int idx)
	: model(m), view(v), index(idx) {}

void ShowSlidesCommand::execute() {
	int count = model.getSlideCount();
	if (count == 0) {
		view.showNoSlides();
		return;
	}

	if (index >= 0) {
		if (!model.isValidSlide(index)) {
			view.showInvalidSlideIndex();
			return;
		}
		view.showSlide(index, model.getSlideTitle(index));
		const auto& shapes = model.getShapes(index);
		for (size_t i = 0; i < shapes.size(); ++i) {
			if (shapes[i]) shapes[i]->draw();
		}
		return;
	}

	for (int i = 0; i < count; ++i) {
		view.showSlide(i, model.getSlideTitle(i));
		const auto& shapes = model.getShapes(i);
		for (size_t s = 0; s < shapes.size(); ++s) {
			if (shapes[s]) shapes[s]->draw();
		}
	}
}

void ShowSlidesCommand::undo() {}

bool ShowSlidesCommand::isUndoable() const { return false; }


SelectSlideCommand::SelectSlideCommand(Model& m, IView& v, int idx)
    : model(m), view(v), index(idx) {}

void SelectSlideCommand::execute() {
    if (!model.isValidSlide(index)) {
        view.showInvalidSlideIndex();
        return;
    }
    previousSlide = model.getCurrentSlide();
    if (model.setCurrentSlide(index)) {
        view.showMessage(std::string("Selected slide ") + std::to_string(index));
    }
}

void SelectSlideCommand::undo() {
    if (previousSlide >= 0) {
        model.setCurrentSlide(previousSlide);
        view.showMessage(std::string("Restored to slide ") + std::to_string(previousSlide));
    }
}

bool SelectSlideCommand::isUndoable() const { return true; }


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

MoveShapeCommand::MoveShapeCommand(Model& m, IView& v, int sIdx, int shIdx, int x, int y)
	: model(m), view(v), slideIndex(sIdx), shapeIndex(shIdx), newX(x), newY(y) {}

void MoveShapeCommand::execute() {
	auto& shapes = model.getShapes(slideIndex);
	if (slideIndex < 0 || slideIndex >= model.getSlideCount() ||
		shapeIndex < 0 || shapeIndex >= static_cast<int>(shapes.size())) {
		view.showMessage("Invalid slide or shape index");
		return;
	}

	oldX = oldY = 0;
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

DeleteShapeCommand::DeleteShapeCommand(Model& m, IView& v, int sIdx, int shIdx)
	: model(m), view(v), slideIndex(sIdx), shapeIndex(shIdx) {}

void DeleteShapeCommand::execute() {
	if (slideIndex < 0 || slideIndex >= model.getSlideCount()) {
		view.showMessage("Invalid slide index");
		return;
	}

	auto shp = model.removeShape(slideIndex, shapeIndex);
	if (!shp) {
		view.showMessage("Invalid shape index");
		return;
	}

	removedShape = shp;
	deleted = true;

	view.showMessage("Shape deleted");
}

void DeleteShapeCommand::undo() {
	if (!deleted) return;

	if (model.addShape(slideIndex, shapeIndex, removedShape)) {
		view.showMessage("Undo: Shape restored");
	} else {
		view.showMessage("Undo failed: could not restore shape");
	}
}

bool DeleteShapeCommand::isUndoable() const {
	return true;
}