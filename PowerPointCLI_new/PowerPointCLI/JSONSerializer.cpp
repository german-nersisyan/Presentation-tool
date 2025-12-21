#include "JSONSerializer.h"
#include "Shapes.h"
#include <fstream>
#include <nlohmann\json.hpp>

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
				sh["color"] = r->getColor();
				sh["filled"] = r->isFilled();
			}
			else if (s->type() == "Square") {
				auto sq = std::dynamic_pointer_cast<SquareShape>(s);
				sh["size"] = sq->getSize();
				sh["color"] = sq->getColor();
				sh["filled"] = sq->isFilled();
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
				model.addShapeToCurrentSlide(
					std::make_shared<RectangleShape>(
						sh["width"], sh["height"],
						sh["color"], sh["filled"]
						)
				);
			}
			else if (type == "Square") {
				model.addShapeToCurrentSlide(
					std::make_shared<SquareShape>(
						sh["size"], sh["color"], sh["filled"]
						)
				);
			}
		}
	}

	return true;
}