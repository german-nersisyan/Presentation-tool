#include "SVGRenderer.h"
#include "Shapes.h"
#include <fstream>
#include <sstream>

bool SVGRenderer::renderSlide(const Model& model, int slideIndex, const std::string& filename) const {
	if (slideIndex < 0 || slideIndex >= model.getSlideCount())
		return false;

	std::ofstream out(filename);
	if (!out.is_open())
		return false;

	out << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\">\n";
	out << "<rect width=\"100%\" height=\"100%\" fill=\"white\" />\n";

	const auto& shapes = model.getShapes(slideIndex);

	for (const auto& shape : shapes) {
		out << shape->toSvg() << "\n";
	}

	out << "</svg>\n";
	out.close();
	return true;
}