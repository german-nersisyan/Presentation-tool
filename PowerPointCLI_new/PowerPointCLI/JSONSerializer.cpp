#include "JSONSerializer.h"
#include "Shapes.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

bool JSONSerializer::save(const Model& model, const std::string& filename) const {
	json j;
	j["slides"] = json::array();

	for (int i = 0; i < model.getSlideCount(); ++i) {
		json slide;
		slide["title"] = model.getSlideTitle(i);
		slide["shapes"] = json::array();

		const auto& shapes = model.getShapes(i);
		for (const auto& s : shapes) {
			json sh;
			sh["type"] = s->type();

			if (s->type() == "Rectangle") {
				auto r = std::dynamic_pointer_cast<RectangleShape>(s);
				sh["width"] = r->getWidth();
				sh["height"] = r->getHeight();
				sh["x"] = r->getX();
				sh["y"] = r->getY();
				sh["color"] = r->getColor();
				sh["filled"] = r->isFilled();
			}
			else if (s->type() == "Square") {
				auto sq = std::dynamic_pointer_cast<SquareShape>(s);
				sh["size"] = sq->getSize();
				sh["x"] = sq->getX();
				sh["y"] = sq->getY();
				sh["color"] = sq->getColor();
				sh["filled"] = sq->isFilled();
			}
			else if (s->type() == "Circle") {
				auto c = std::dynamic_pointer_cast<CircleShape>(s);
				sh["radius"] = c->getRadius();
				sh["x"] = c->getX();
				sh["y"] = c->getY();
				sh["filled"] = c->isFilled();
			}
			else if (s->type() == "Triangle") {
				auto t = std::dynamic_pointer_cast<TriangleShape>(s);
				sh["side"] = t->getSide();
				sh["x"] = t->getX();
				sh["y"] = t->getY();
				sh["color"] = t->getColor();
				sh["filled"] = t->isFilled();
			}

			slide["shapes"].push_back(sh);
		}

		j["slides"].push_back(slide);
	}

	std::ofstream file(filename);
	if (!file.is_open()) return false;

	file << j.dump(4);
	return true;
}

bool JSONSerializer::load(Model& model, const std::string& filename) const {
	std::ifstream file(filename);
	if (!file.is_open()) return false;

	json j;
	file >> j;

	model.clear();

	for (const auto& slide : j["slides"]) {
		model.addSlide(slide["title"]);

		for (const auto& sh : slide["shapes"]) {
			std::string type = sh["type"];

			if (type == "Rectangle") {
				int x = sh.contains("x") ? sh["x"].get<int>() : 0;
				int y = sh.contains("y") ? sh["y"].get<int>() : 0;
				model.addShapeToCurrentSlide(
					std::make_shared<RectangleShape>(
						sh["width"], sh["height"], x, y,
						sh["color"], sh["filled"]
						)
				);
			}
			else if (type == "Square") {
				int x = sh.contains("x") ? sh["x"].get<int>() : 0;
				int y = sh.contains("y") ? sh["y"].get<int>() : 0;
				model.addShapeToCurrentSlide(
					std::make_shared<SquareShape>(
						sh["size"], x, y,
						sh["color"], sh["filled"]
						)
				);
			}
			else if (type == "Circle") {
				int x = sh.contains("x") ? sh["x"].get<int>() : 0;
				int y = sh.contains("y") ? sh["y"].get<int>() : 0;
				model.addShapeToCurrentSlide(
					std::make_shared<CircleShape>(
						sh["radius"], x, y,
						sh["filled"]
						)
				);
			}
			else if (type == "Triangle") {
				int x = sh.contains("x") ? sh["x"].get<int>() : 0;
				int y = sh.contains("y") ? sh["y"].get<int>() : 0;
				model.addShapeToCurrentSlide(
					std::make_shared<TriangleShape>(
						sh["side"], x, y,
						sh["color"], sh["filled"]
						)
				);
			}
		}
	}

	return true;
}