#include "Commands.h"

AddSlideCommand::AddSlideCommand(const std::string& t, Model& m, IView& v)
	: title(t), model(m), view(v) {}

void AddSlideCommand::execute() {
	model.addSlide(title);
	view.showAddedSlide(title, model.getSlideCount());
}

RemoveSlideCommand::RemoveSlideCommand(int idx, Model& m, IView& v)
	: index(idx), model(m), view(v) {}

void RemoveSlideCommand::execute() {
	if (model.removeSlide(index)) {
		view.showRemovedSlide(std::to_string(index));
	}
	else {
		view.showInvalidSlideIndex();
	}
}

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
		int width = options.count("-width") ? std::stoi(options.at("-width")) : 100;
		int height = options.count("-height") ? std::stoi(options.at("-height")) : 50;
		shape = std::make_shared<RectangleShape>(width, height, color, filled);
	}
	else if (type == "square") {
		int size = options.count("-size") ? std::stoi(options.at("-size")) : 50;
		shape = std::make_shared<SquareShape>(size, color, filled);
	}
	else if (type == "triangle") {
		int side = options.count("-side") ? std::stoi(options.at("-side")) : 50;
		shape = std::make_shared<TriangleShape>(side, color, filled);
	}
	else if (type == "circle") {
		int radius = options.count("-radius") ? std::stoi(options.at("-radius")) : 25;
		int x = options.count("-x") ? std::stoi(options.at("-x")) : 0;
		int y = options.count("-y") ? std::stoi(options.at("-y")) : 0;
		shape = std::make_shared<CircleShape>(radius, x, y, filled);
	}
	else {
		view.showMessage("Unknown shape type: " + type);
		return;
	}

	model.addShapeToCurrentSlide(shape);

	std::string slideTitle = model.getSlideTitle(model.getCurrentSlide());

	int widthOrRadius = 0;
	int heightOrSide = 0;

	if (type == "circle") {
		auto circle = std::dynamic_pointer_cast<CircleShape>(shape);
		widthOrRadius = circle->getRadius();
		heightOrSide = 0;
	}
	else if (type == "triangle") {
		auto tri = std::dynamic_pointer_cast<TriangleShape>(shape);
		widthOrRadius = tri->getSide();
		heightOrSide = 0;
	}
	else if (type == "square") {
		auto sq = std::dynamic_pointer_cast<SquareShape>(shape);
		widthOrRadius = sq->getSize();
		heightOrSide = sq->getSize();
	}
	else if (type == "rectangle") {
		auto rect = std::dynamic_pointer_cast<RectangleShape>(shape);
		widthOrRadius = rect->getWidth();
		heightOrSide = rect->getHeight();
	}

	view.showAddedShape(type, widthOrRadius, heightOrSide, slideTitle, filled);
}

ListSlidesCommand::ListSlidesCommand(Model& m, IView& v)
	: model(m), view(v) {}

void ListSlidesCommand::execute() {
	int count = model.getSlideCount();
	if (count == 0) {
		view.showNoSlides();
		return;
	}

	for (int i = 0; i < count; ++i) {
		view.showSlide(i, model.getSlideTitle(i));
	}
}

void HelpCommand::execute() {
	view.showMessage("Available commands:");

	for (const auto& name : registry.getAllCommandNames()) {
		std::string desc;

		if (name == "add-slide") desc = "add-slide -title <title> [-background <color>] [-public]";
		else if (name == "remove-slide") desc = "remove-slide -index <slide_index>";
		else if (name == "add-shape") desc = "add-shape -type <type> [...options] [-filled]";
		else if (name == "list-slides") desc = "list-slides";
		else if (name == "show-slide") desc = "Show a slide's content. Options: -index N or -all flag";
		else if (name == "help") desc = "help";

		view.showMessage("  " + name + " : " + desc);
	}
}

void ShowSlideCommand::execute() {
	if (showAll) {
		for (int i = 0; i < model.getSlideCount(); ++i) {
			ShowSlideCommand cmd(model, view, i, false);
			cmd.execute();
		}
		return;
	}

	if (index < 0 || index >= model.getSlideCount()) {
		view.showInvalidSlideIndex();
		return;
	}

	const auto& title = model.getSlideTitle(index);
	view.showMessage("Slide " + std::to_string(index) + ": " + title);

	const auto& shapes = model.getShapes(index);
	if (shapes.empty()) {
		view.showMessage("  No shapes on this slide.");
		return;
	}

	for (size_t i = 0; i < shapes.size(); ++i) {
		const auto& shape = shapes[i];
		std::string info = "  Shape " + std::to_string(i) + ": " + shape->type();

		if (shape->type() == "Rectangle") {
			auto rect = std::dynamic_pointer_cast<RectangleShape>(shape);
			info += " (" + std::to_string(rect->getWidth()) + "x" +
				std::to_string(rect->getHeight()) + ", color=" + rect->getColor() + ")";
		}
		else if (shape->type() == "Square") {
			auto sq = std::dynamic_pointer_cast<SquareShape>(shape);
			info += " (" + std::to_string(sq->getSize()) + "x" +
				std::to_string(sq->getSize()) + ", color=" + sq->getColor() + ")";
		}
		else if (shape->type() == "Triangle") {
			auto tri = std::dynamic_pointer_cast<TriangleShape>(shape);
			info += " (side=" + std::to_string(tri->getSide()) + ", color=" + tri->getColor() + ")";
		}
		else if (shape->type() == "Circle") {
			auto circ = std::dynamic_pointer_cast<CircleShape>(shape);
			info += " (radius=" + std::to_string(circ->getRadius()) +
				", center=(" + std::to_string(circ->getX()) + "," +
				std::to_string(circ->getY()) + "))";
		}

		view.showMessage(info);
	}
}