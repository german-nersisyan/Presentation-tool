#include "JSONSerializer.h"
#include "Shapes.h"
#include "ShapeFactory.h"
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
			// delegate serialization to shape
			slide["shapes"].push_back(s->toJson());
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
	ShapeFactory sf;

	for (const auto& slide : j["slides"]) {
		model.addSlide(slide["title"]);

		for (const auto& sh : slide["shapes"]) {
			auto shape = sf.fromJson(sh);
			if (shape) {
				// best-effort: ignore failures when loading shapes
				model.addShapeToCurrentSlide(shape);
			}
		}
	}

	return true;
}